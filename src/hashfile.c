#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hashfile.h"
#include "../include/quadra.h"
#include "../include/criarSvg.h"

#define BUCKET_SIZE 30
#define MAX_CHAVE 30

typedef struct{
    int profundidade_local;
    int num_registros;
}cabecalho;

typedef struct{
    FILE *arq_buckets;
    FILE* arq_dir;
    size_t tamanho_registro;
    int profundidade_global;
    int tamanho_diretorio;
    long *pont;
}hashfile;

unsigned int calcular_hash(char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void dobrar_diretorio(hashfile *hf) {
    int tamanho_antigo = hf->tamanho_diretorio;
    
    hf->profundidade_global++;
    hf->tamanho_diretorio = 1 << hf->profundidade_global; 

    long *novo_diretorio = malloc(hf->tamanho_diretorio * sizeof(long));

    for (int i = 0; i < tamanho_antigo; i++) {
        novo_diretorio[i] = hf->pont[i];
        novo_diretorio[i + tamanho_antigo] = hf->pont[i]; 
    }

    free(hf->pont);
    hf->pont = novo_diretorio;
}

void dividir_bucket(hashfile *hf, int indice_dir) {
    long offset_velho = hf->pont[indice_dir];
    size_t tamanho_linha = MAX_CHAVE + hf->tamanho_registro;

    cabecalho cab_velho;
    fseek(hf->arq_buckets, offset_velho, SEEK_SET);
    fread(&cab_velho, sizeof(cabecalho), 1, hf->arq_buckets);

    void *buffer_registros = malloc(BUCKET_SIZE * tamanho_linha);
    fread(buffer_registros, tamanho_linha, BUCKET_SIZE, hf->arq_buckets);

    cab_velho.profundidade_local++;
    cab_velho.num_registros = 0;

    cabecalho cab_novo;
    cab_novo.profundidade_local = cab_velho.profundidade_local;
    cab_novo.num_registros = 0;

    fseek(hf->arq_buckets, 0, SEEK_END);
    long offset_novo = ftell(hf->arq_buckets);

    int num_bits = cab_velho.profundidade_local;
    int mascara_local = (1 << num_bits) - 1;
    
    int bit_diferenciador = 1 << (num_bits - 1);
    int padrao_novo = (indice_dir & mascara_local) | bit_diferenciador;

    for (int i = 0; i < hf->tamanho_diretorio; i++) {
        if ((i & mascara_local) == padrao_novo) {
            hf->pont[i] = offset_novo;
        }
    }

    void *espaco_vazio = calloc(BUCKET_SIZE, tamanho_linha);
    
    fseek(hf->arq_buckets, offset_velho, SEEK_SET);
    fwrite(&cab_velho, sizeof(cabecalho), 1, hf->arq_buckets);
    fwrite(espaco_vazio, tamanho_linha, BUCKET_SIZE, hf->arq_buckets);

    fseek(hf->arq_buckets, offset_novo, SEEK_SET);
    fwrite(&cab_novo, sizeof(cabecalho), 1, hf->arq_buckets);
    fwrite(espaco_vazio, tamanho_linha, BUCKET_SIZE, hf->arq_buckets);
    
    free(espaco_vazio);

    for (int i = 0; i < BUCKET_SIZE; i++) {
        char *chave_temp = (char *) (buffer_registros + (i * tamanho_linha));
        void *dado_temp = buffer_registros + (i * tamanho_linha) + MAX_CHAVE;
        
        inserir_registro((Hashfile)hf, chave_temp, dado_temp);
    }

    free(buffer_registros);
}

Hashfile inicializar_hashfile(char* nome_base, size_t tamanho_registro) {
    hashfile* hf = malloc(sizeof(hashfile));
    if (hf == NULL) return NULL;

    char nome_hf[256], nome_hfc[256];
    sprintf(nome_hf, "%s.hf", nome_base);
    sprintf(nome_hfc, "%s.hfc", nome_base);

    hf->arq_buckets = fopen(nome_hf, "w+b");
    hf->arq_dir = fopen(nome_hfc, "w+b");

    if (hf->arq_buckets == NULL || hf->arq_dir == NULL) {
        free(hf);
        return NULL;
    }

    hf->tamanho_registro = tamanho_registro;
    hf->profundidade_global = 1;
    hf->tamanho_diretorio = 2;
    hf->pont = malloc(hf->tamanho_diretorio * sizeof(long));

    cabecalho bucket_inicial;
    bucket_inicial.profundidade_local = 0; 
    bucket_inicial.num_registros = 0;

    long offset_bucket = 0; 
    
    hf->pont[0] = offset_bucket;
    hf->pont[1] = offset_bucket;

    fseek(hf->arq_dir, 0, SEEK_SET);
    fwrite(hf->pont, sizeof(long), hf->tamanho_diretorio, hf->arq_dir);
    fflush(hf->arq_dir);

    fseek(hf->arq_buckets, offset_bucket, SEEK_SET);
    fwrite(&bucket_inicial, sizeof(cabecalho), 1, hf->arq_buckets);

    size_t tamanho_linha = MAX_CHAVE + hf->tamanho_registro; 
    void *espaco_vazio = calloc(BUCKET_SIZE, tamanho_linha); 
    
    fwrite(espaco_vazio, tamanho_linha, BUCKET_SIZE, hf->arq_buckets);
    free(espaco_vazio);
    fflush(hf->arq_buckets);

    return (Hashfile) hf;
}

void fechar_hashfile(Hashfile hf_ptr) {
    if (hf_ptr == NULL) return;

    hashfile* hf = (hashfile *) hf_ptr;

    rewind(hf->arq_dir);
    
    fwrite(&hf->profundidade_global, sizeof(int), 1, hf->arq_dir);
    fwrite(&hf->tamanho_registro, sizeof(size_t), 1, hf->arq_dir);
    fwrite(hf->pont, sizeof(long), hf->tamanho_diretorio, hf->arq_dir);

    if (hf->arq_buckets) fclose(hf->arq_buckets);
    if (hf->arq_dir) fclose(hf->arq_dir);
    if (hf->pont) free(hf->pont);

    free(hf);
}

int inserir_registro(Hashfile hf_ptr, char* chave, void* dado) {
    hashfile *hf = (hashfile *) hf_ptr;
    if (hf == NULL || chave == NULL || dado == NULL) return 0;

    unsigned int hash_val = calcular_hash(chave);

    if (hf->profundidade_global > 20) {
        printf("\n[ERRO FATAL] Loop infinito detectado no Hashing Extensível.\n");
        printf("A chave causadora é: '%s' | Valor do Hash: %u\n", chave, hash_val);
        
        printf("Qual Tabela travou? -> Tamanho do registro: %zu ", hf->tamanho_registro);
        if (hf->tamanho_registro == 48) printf("(Tabela de QUADRAS)\n");
        else if (hf->tamanho_registro == 284) printf("(Tabela de PESSOAS)\n");
        else if (hf->tamanho_registro == 8208) printf("(Tabela de INDICE)\n");
        else printf("(Tabela Desconhecida)\n");
        
        exit(1); 
    }

    int mascara = (1 << hf->profundidade_global) - 1;
    int indice_dir = hash_val & mascara;
    
    long offset_bucket = hf->pont[indice_dir];

    cabecalho cabecalho;
    fseek(hf->arq_buckets, offset_bucket, SEEK_SET);
    fread(&cabecalho, sizeof(cabecalho), 1, hf->arq_buckets);

    size_t tamanho_linha = MAX_CHAVE + hf->tamanho_registro;

    long offset_base_registros = offset_bucket + sizeof(cabecalho);
    
    for (int i = 0; i < cabecalho.num_registros; i++) {
        char chave_existente[MAX_CHAVE] = {0};
        long offset_atual = offset_base_registros + (i * tamanho_linha);
        fseek(hf->arq_buckets, offset_atual, SEEK_SET);
        fread(chave_existente, sizeof(char), MAX_CHAVE, hf->arq_buckets);
        if (strcmp(chave_existente, chave) == 0) {
            fseek(hf->arq_buckets, offset_atual + MAX_CHAVE, SEEK_SET);
            fwrite(dado, hf->tamanho_registro, 1, hf->arq_buckets);
            return 1; 
        }
    }

    if (cabecalho.num_registros < BUCKET_SIZE) {
        
        long offset_novo_registro = offset_bucket + sizeof(cabecalho) + (cabecalho.num_registros * tamanho_linha);
        fseek(hf->arq_buckets, offset_novo_registro, SEEK_SET);

        char buffer_chave[MAX_CHAVE] = {0};
        strncpy(buffer_chave, chave, MAX_CHAVE - 1);
        
        fwrite(buffer_chave, sizeof(char), MAX_CHAVE, hf->arq_buckets);
        fwrite(dado, hf->tamanho_registro, 1, hf->arq_buckets);

        cabecalho.num_registros++;
        fseek(hf->arq_buckets, offset_bucket, SEEK_SET);
        fwrite(&cabecalho, sizeof(cabecalho), 1, hf->arq_buckets);

        return 1;
    }

    if (cabecalho.profundidade_local == hf->profundidade_global) {
        dobrar_diretorio(hf);
        
        mascara = (1 << hf->profundidade_global) - 1;
        indice_dir = hash_val & mascara;
    }

    dividir_bucket(hf, indice_dir);
    return inserir_registro(hf_ptr, chave, dado);
}

int buscar_registro(Hashfile hf, char* chave_buscada, void* dado_retorno) {
    if (hf == NULL || chave_buscada == NULL || dado_retorno == NULL) {
        return 0; 
    }

    hashfile* hf_interno = (hashfile*)hf;

    unsigned int valor_hash = calcular_hash(chave_buscada);

    int mascara = (1 << hf_interno->profundidade_global) - 1;
    int indice_diretorio = valor_hash & mascara;

    long offset_bucket = hf_interno->pont[indice_diretorio];

    fseek(hf_interno->arq_buckets, offset_bucket, SEEK_SET);

    cabecalho cab;
    if (fread(&cab, sizeof(cabecalho), 1, hf_interno->arq_buckets) != 1) {
        return 0;
    }

    char chave_lida[MAX_CHAVE];
    
    for (int i = 0; i < cab.num_registros; i++) {
        fread(chave_lida, sizeof(char), MAX_CHAVE, hf_interno->arq_buckets);

        if (strcmp(chave_lida, chave_buscada) == 0) {
            fread(dado_retorno, hf_interno->tamanho_registro, 1, hf_interno->arq_buckets);
            return 1;
        } else {
            fseek(hf_interno->arq_buckets, hf_interno->tamanho_registro, SEEK_CUR);
        }
    }

    return 0;
}

int remover_registro(Hashfile hf, char* chave_removida) {
    if (hf == NULL || chave_removida == NULL) {
        return 0; 
    }

    hashfile* hf_interno = (hashfile*)hf;
    
    unsigned int valor_hash = calcular_hash(chave_removida);
    int mascara = (1 << hf_interno->profundidade_global) - 1;
    int indice_diretorio = valor_hash & mascara;
    long offset_bucket = hf_interno->pont[indice_diretorio];

    fseek(hf_interno->arq_buckets, offset_bucket, SEEK_SET);
    cabecalho cab;
    if (fread(&cab, sizeof(cabecalho), 1, hf_interno->arq_buckets) != 1) {
        return 0;
    }

    char chave_lida[MAX_CHAVE];
    long pos_registro_atual;

    for (int i = 0; i < cab.num_registros; i++) {
        pos_registro_atual = ftell(hf_interno->arq_buckets); 
        
        fread(chave_lida, sizeof(char), MAX_CHAVE, hf_interno->arq_buckets);

        if (strcmp(chave_lida, chave_removida) == 0) {
            if (i < cab.num_registros - 1) {
                
                long pos_ultimo_registro = offset_bucket + sizeof(cabecalho) + (cab.num_registros - 1) * (MAX_CHAVE + hf_interno->tamanho_registro);
                
                fseek(hf_interno->arq_buckets, pos_ultimo_registro, SEEK_SET);
                char ultima_chave[MAX_CHAVE];
                fread(ultima_chave, sizeof(char), MAX_CHAVE, hf_interno->arq_buckets);
                
                void* buffer_dado = malloc(hf_interno->tamanho_registro);
                fread(buffer_dado, hf_interno->tamanho_registro, 1, hf_interno->arq_buckets);

                fseek(hf_interno->arq_buckets, pos_registro_atual, SEEK_SET);
                fwrite(ultima_chave, sizeof(char), MAX_CHAVE, hf_interno->arq_buckets);
                fwrite(buffer_dado, hf_interno->tamanho_registro, 1, hf_interno->arq_buckets);
                
                free(buffer_dado);
            }

            cab.num_registros--;
            
            fseek(hf_interno->arq_buckets, offset_bucket, SEEK_SET);
            fwrite(&cab, sizeof(cabecalho), 1, hf_interno->arq_buckets);

            fflush(hf_interno->arq_buckets); 

            return 1;
        } else {
            fseek(hf_interno->arq_buckets, hf_interno->tamanho_registro, SEEK_CUR);
        }
    }

    return 0; 
}

void desenha_quadras_svg(Hashfile* hf_quadra, FILE* svg, Estilo e) {
    hashfile* hf = (hashfile*)hf_quadra;
    FILE* arquivo_dados = hf->arq_buckets;
    
    rewind(arquivo_dados); 

    cabecalho cab;
    void* temp = malloc(hf->tamanho_registro); 
    char chave_temp[MAX_CHAVE]; // Precisamos ler a chave para o fread não se perder

    // Lê o arquivo saltando de balde em balde
    while (fread(&cab, sizeof(cabecalho), 1, arquivo_dados) == 1) {
        
        // Percorre os slots internos do balde
        for (int i = 0; i < BUCKET_SIZE; i++) {
            
            // 1. Lê a chave (mantém o ponteiro de leitura sincronizado)
            fread(chave_temp, sizeof(char), MAX_CHAVE, arquivo_dados);
            
            // 2. Lê a struct da Quadra em si
            fread(temp, hf->tamanho_registro, 1, arquivo_dados);
            
            // 3. O cabeçalho dita se essa posição tem uma quadra válida
            if (i < cab.num_registros) {
                Quadra q = (Quadra)temp; 
                insere_quadra_svg(svg, q, e); // Sua função de impressão!
            }
        }
    }

    free(temp);
}

void testar_qtd_pessoas(Hashfile* hf_pessoa) {
    hashfile* hf = (hashfile*) hf_pessoa;
    FILE* arq = hf->arq_buckets;
    rewind(arq); 

    cabecalho cab;
    int contador = 0;
    int slots_vazios = 0;

    // Lemos o arquivo pulando de balde em balde
    while (fread(&cab, sizeof(cabecalho), 1, arq) == 1) {
        
        // Entramos dentro do balde e lemos todas as "gavetas"
        for (int i = 0; i < BUCKET_SIZE; i++) {
            
            // 1. Lemos a chave (para não dessincronizar o ponteiro)
            char chave[MAX_CHAVE];
            fread(chave, sizeof(char), MAX_CHAVE, arq);
            
            // 2. Lemos o dado real
            void* temp = malloc(hf->tamanho_registro);
            fread(temp, hf->tamanho_registro, 1, arq);
            
            // O cabeçalho nos diz exatamente quantos registros são válidos neste balde!
            if (i < cab.num_registros) {
                contador++; // É um habitante real!
            } else {
                slots_vazios++; // É lixo de memória / espaço reservado
            }
            
            free(temp);
        }
    }

    printf("[NOVO DIAGNÓSTICO] Pessoas válidas no Hash: %d\n", contador);
    printf("--------------------------------------------------\n");
}

void testar_qtd_quadras(Hashfile* hf_quadra) {
    hashfile* hf = (hashfile*) hf_quadra;
    FILE* arq = hf->arq_buckets;
    rewind(arq); 

    cabecalho cab;
    int contador = 0;
    int slots_vazios = 0;

    // Lemos o arquivo pulando de balde em balde
    while (fread(&cab, sizeof(cabecalho), 1, arq) == 1) {
        
        // Entramos dentro do balde e lemos todas as "gavetas"
        for (int i = 0; i < BUCKET_SIZE; i++) {
            
            // 1. Lemos a chave (para não dessincronizar o ponteiro)
            char chave[MAX_CHAVE];
            fread(chave, sizeof(char), MAX_CHAVE, arq);
            
            // 2. Lemos o dado real
            void* temp = malloc(hf->tamanho_registro);
            fread(temp, hf->tamanho_registro, 1, arq);
            
            // O cabeçalho nos diz exatamente quantos registros são válidos neste balde!
            if (i < cab.num_registros) {
                contador++; // É um habitante real!
            } else {
                slots_vazios++; // É lixo de memória / espaço reservado
            }
            
            free(temp);
        }
    }

    printf("[NOVO DIAGNÓSTICO] Quadras válidas no Hash: %d\n", contador);
    printf("--------------------------------------------------\n");
}