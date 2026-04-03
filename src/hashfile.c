#include "../include/hashfile.h"
#include <string.h>
#include <stdlib.h>

#define BUCKET_SIZE 30

typedef struct{
    int chave;
    char dados[100];
}registro;

typedef struct{
    int profundidade_local;
    int num_registros;
    registro registros[BUCKET_SIZE];
}bucket;

typedef struct{
    int profundidade_global;
    long* pont;
}diretorio;

int calcular_hash(int chave) {
    unsigned int x = (unsigned int)chave;
    
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    
    return (int)x;
}

int obter_indice_diretorio(int chave, int prof_global) {
    int hash = calcular_hash(chave);
    
    int mascara = (1 << prof_global) - 1;
    
    return hash & mascara;
}

void dobrar_diretorio(FILE* f_dir){
    int prof_global;
    fseek(f_dir, 0, SEEK_SET);
    fread(&prof_global, sizeof(int), 1, f_dir);

    int tamanho_atual = 1 << prof_global;

    long* pont = (long*)malloc(tamanho_atual * sizeof(long));
    fread(pont, sizeof(long), tamanho_atual, f_dir);

    prof_global++;
    fseek(f_dir, 0, SEEK_SET);
    fwrite(&prof_global, sizeof(int), 1, f_dir);

    fwrite(pont, sizeof(long), tamanho_atual, f_dir);
    fwrite(pont, sizeof(long), tamanho_atual, f_dir);

    free(pont);
}

void atualizar_ponteiros_diretorio(FILE *f_dir, int mascara_local, int hash_base_antigo, long offset_novo, long offset_antigo){
    int prof_global;
    fseek(f_dir, 0, SEEK_SET);
    fread(&prof_global, sizeof(int), 1, f_dir);
    
    int tamanho_dir = 1 << prof_global;
    long ponteiro_atual;
    
    for (int i = 0; i < tamanho_dir; i++) {
        fseek(f_dir, sizeof(int) + (i * sizeof(long)), SEEK_SET);
        fread(&ponteiro_atual, sizeof(long), 1, f_dir);
        
        if (ponteiro_atual == offset_antigo) {
            
            if ((i & mascara_local) != hash_base_antigo) {
                fseek(f_dir, sizeof(int) + (i * sizeof(long)), SEEK_SET);
                
                fwrite(&offset_novo, sizeof(long), 1, f_dir);
            }
        }
    }
}

void dividir_bucket(FILE* f_dir, FILE* f_buck, long offset_antigo, bucket* b_antigo, registro novo_reg){
    bucket b_novo;
    b_novo.num_registros = 0;
    b_novo.profundidade_local = b_antigo->profundidade_local + 1;
    b_antigo->profundidade_local += 1;
    
    registro todos_registros[BUCKET_SIZE + 1];
    for (int i = 0; i < BUCKET_SIZE; i++) {
        todos_registros[i] = b_antigo->registros[i];
    }
    todos_registros[BUCKET_SIZE] = novo_reg;
    
    b_antigo->num_registros = 0; 

    int mascara_local = (1 << b_antigo->profundidade_local) - 1;
    
    int hash_base_antigo = calcular_hash(todos_registros[0].chave) & mascara_local;

    for (int i = 0; i < BUCKET_SIZE + 1; i++) {
        int hash_reg = calcular_hash(todos_registros[i].chave);
        int bits_locais = hash_reg & mascara_local;
        
        if (bits_locais == hash_base_antigo) {
            b_antigo->registros[b_antigo->num_registros++] = todos_registros[i];
        } else {
            b_novo.registros[b_novo.num_registros++] = todos_registros[i];
        }
    }
    
    fseek(f_buck, offset_antigo, SEEK_SET);
    fwrite(b_antigo, sizeof(bucket), 1, f_buck);
    
    fseek(f_buck, 0, SEEK_END);
    long offset_novo = ftell(f_buck);
    fwrite(&b_novo, sizeof(bucket), 1, f_buck);
    
    atualizar_ponteiros_diretorio(f_dir, mascara_local, hash_base_antigo, offset_novo,offset_antigo);
}

void hashfile_split(FILE* f_dir, FILE* f_buck, long offset_bucket, bucket b, registro reg) {
    int prof_global;
    
    fseek(f_dir, 0, SEEK_SET);
    fread(&prof_global, sizeof(int), 1, f_dir);

    if (b.profundidade_local == prof_global) {
        printf("Profundidade local igual a global (%d). Dobrando o diretorio...\n", prof_global);
        dobrar_diretorio(f_dir);
        
        prof_global++; 
    }

    printf("Dividindo o bucket e redistribuindo os dados...\n");
    dividir_bucket(f_dir, f_buck, offset_bucket, &b, reg);
}

void inicializar_hashfile(char* nome_dir, char* nome_buckets){
    FILE* f_dir = fopen(nome_dir, "wb+");
    FILE* f_buck = fopen(nome_buckets, "wb+");

    if(!f_dir || !f_buck){
        printf("Erro ao criar arquivos de hash\n");
        if(f_dir) fclose(f_dir);
        if(f_buck) fclose(f_buck);
        return;
    }

    int prof_global = 1;
    fwrite(&prof_global, sizeof(int), 1, f_dir);

    bucket b_inicial;
    b_inicial.profundidade_local = 1;
    b_inicial.num_registros = 0;
    memset(b_inicial.registros, 0, sizeof(b_inicial.registros));

    long offset_inicial = 0;
    fwrite(&b_inicial, sizeof(bucket), 1, f_buck);

    fwrite(&offset_inicial, sizeof(long), 1, f_dir);
    fwrite(&offset_inicial, sizeof(long), 1, f_dir);

    fclose(f_dir);
    fclose(f_buck);
}

int inserir_registro(char* nome_dir, char* nome_buckets, Registro reg){
    registro* var = (registro*) reg;
    FILE* f_dir = fopen(nome_dir, "rb+");
    FILE* f_buck = fopen(nome_buckets, "rb+");

    if(!f_dir || !f_buck){
        printf("Nao foi possível abrir os arquivos.\n");
        if(f_dir) fclose(f_dir);
        if(f_buck) fclose(f_buck);
        return 0;
    }

    int prof_global;
    fread(&prof_global, sizeof(int), 1, f_dir);

    int indice = obter_indice_diretorio(var->chave, prof_global);
    long offset_bucket;

    fseek(f_dir, sizeof(int) + (indice * sizeof(long)), SEEK_SET);
    fread(&offset_bucket, sizeof(long), 1, f_dir);

    bucket b;
    fseek(f_buck, offset_bucket, SEEK_SET);
    fread(&b, sizeof(bucket), 1, f_buck);

    if(b.num_registros<BUCKET_SIZE){
        b.registros[b.num_registros] = *var;
        b.num_registros++;

        fseek(f_buck, offset_bucket, SEEK_SET);
        fwrite(&b, sizeof(bucket),  1, f_buck);

        fclose(f_dir);
        fclose(f_buck);
        return 1;
    }

    printf("Bucket cheio, fazendo split");
    hashfile_split(f_dir, f_buck, offset_bucket, b, *var);

    fclose(f_dir);
    fclose(f_buck);

    return 1;
}

Registro buscar_registro(char* n_dir, char* n_buck, int chave_buscada) {
    FILE *f_dir = fopen(n_dir, "rb");
    FILE *f_buck = fopen(n_buck, "rb");

    if (!f_dir || !f_buck) {
        if(f_dir) fclose(f_dir);
        if(f_buck) fclose(f_buck);
        return NULL; 
    }

    int prof_global;
    fread(&prof_global, sizeof(int), 1, f_dir);

    int hash = calcular_hash(chave_buscada);
    int mascara = (1 << prof_global) - 1;
    int indice = hash & mascara;

    long offset_bucket;
    fseek(f_dir, sizeof(int) + (indice * sizeof(long)), SEEK_SET);
    fread(&offset_bucket, sizeof(long), 1, f_dir);

    bucket b;
    fseek(f_buck, offset_bucket, SEEK_SET);
    fread(&b, sizeof(bucket), 1, f_buck);

    fclose(f_dir);
    fclose(f_buck);

    for (int i = 0; i < b.num_registros; i++) {
        if (b.registros[i].chave == chave_buscada) {
            registro *encontrado = malloc(sizeof(registro));
            *encontrado = b.registros[i];
            return encontrado;
        }
    }

    return NULL; 
}

int remover_registro(char* n_dir, char* n_buck, int chave_removida){
    FILE* f_dir = fopen(n_dir, "rb+");
    FILE* f_buck = fopen(n_buck, "rb+");

    if(!f_dir || !f_buck){
        printf("Erro ao abrir arquivos para remocao.\n");
        if(f_dir) fclose(f_dir);
        if(f_buck) fclose(f_buck);
        return 0;
    }

    int prof_global;
    fread(&prof_global, sizeof(int), 1, f_dir);

    int indice = obter_indice_diretorio(chave_removida, prof_global);
    long offset_bucket;

    fseek(f_dir, sizeof(int) + (indice * sizeof(long)), SEEK_SET);
    fread(&offset_bucket, sizeof(long), 1, f_dir);

    bucket b;
    fseek(f_buck, offset_bucket, SEEK_SET);
    fread(&b, sizeof(bucket), 1, f_buck);

    int encontrou = 0;
    for(int i = 0; i < b.num_registros; i++) {
        if(b.registros[i].chave == chave_removida) {
            b.registros[i] = b.registros[b.num_registros - 1];
            b.num_registros--; 
            encontrou = 1;
            break;
        }
    }

    if (encontrou) {
        fseek(f_buck, offset_bucket, SEEK_SET);
        fwrite(&b, sizeof(bucket), 1, f_buck);
    }

    fclose(f_dir);
    fclose(f_buck);
    
    return encontrou;
}

Registro criar_registro(int chave, char* dado){
    registro* reg = malloc(sizeof(registro));
    reg->chave = chave;
    strcpy(reg->dados,dado);

    return reg;
}

void modificar_registro(Registro reg, char* dado){
    registro* var = (registro*) reg;
    strcpy(var->dados,dado);
}

int get_chave_registro(Registro reg){
    registro* var = (registro*) reg;
    return var->chave;
}

char* get_dado_reg(Registro reg){
    registro* var = (registro*) reg;
    return var->dados;
}