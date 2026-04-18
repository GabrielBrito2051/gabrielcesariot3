#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hashfile.h"
#include "../include/pessoa.h"
#include "../include/quadra.h"
#include "../include/criarSvg.h"
#include "../include/txt.h"

#define tamLinha 256

void remover_quadra(Hashfile hf_ceps, Hashfile hf_pessoa, char* cep_destruido, FILE* txt){
    IndiceCep alvo = criar_indice_cep();
    Pessoa temp = malloc(SIZE_PESSOA);
    if(buscar_registro(hf_ceps, cep_destruido, alvo)){
        for(int i = 0;i<get_n_cpfs_indice(alvo);i++){
            char* cpf_morador = get_cpf_indice(alvo, i);
            if(buscar_registro(hf_pessoa, cpf_morador, temp)){
                setMorador(temp, 0);
                remover_registro(hf_pessoa, cpf_morador);
                inserir_registro(hf_pessoa, cpf_morador, temp);
                print_rq_txt(txt, temp);
            }
        }
        remover_registro(hf_ceps, cep_destruido);
    }
    free_indice_cep(alvo);
    rip(temp);
}

void pessoas_quadra(Hashfile hf_ceps, Hashfile hf_pessoa, Hashfile hf_quadra, char* cep, FILE* svg){
    IndiceCep procurado = criar_indice_cep();
    Pessoa temp = malloc(SIZE_PESSOA);
    Quadra q = malloc(SIZE_QUADRA);
    int N=0, S=0, E=0, W=0, total=0;
    if(buscar_registro(hf_ceps, cep, procurado)){
        for(int i=0;i<get_n_cpfs_indice(procurado);i++){
            char* cpf_morador = get_cpf_indice(procurado, i);
            if(buscar_registro(hf_pessoa, cpf_morador, temp)){
                char face = getFace(temp);
                if(face=='N'){
                    N++;
                }
                else if(face=='S'){
                    S++;
                }
                else if(face=='L' || face=='E'){
                    E++;
                }
                else if(face=='O' || face=='W'){
                    W++;
                }
            }
        }
        if(buscar_registro(hf_quadra, cep, q)){
            insere_censo_svg(svg, q, N, S, E, W);
        }
    }
    rip(temp);
    liberar_quadra(q);
    free_indice_cep(procurado);
}

void rip_pessoa(Hashfile hf_pessoa, Hashfile hf_ceps, Hashfile hf_quadra, char*cpf, FILE* svg, FILE* txt){
    Pessoa morta = malloc(SIZE_PESSOA);
    Quadra q = malloc(SIZE_QUADRA);
    if(buscar_registro(hf_pessoa, cpf, morta)){
        char cep_antigo[12];
        strcpy(cep_antigo, getCepMorador(morta));
        remover_registro(hf_pessoa, cpf);
        print_rip_txt(txt, morta);
        if(getMorador(morta)){
            IndiceCep temp;
            buscar_registro(hf_quadra, cep_antigo, q);
            insere_rip_svg(svg, q, morta);
            if(buscar_registro(hf_ceps, cep_antigo, temp)){
                for(int i=0;i<get_n_cpfs_indice(temp);i++){
                    if(strcmp(get_cpf_indice(temp, i), cpf)==0){
                        int ultimo = get_n_cpfs_indice(temp) - 1;
                        set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                        int total = get_n_cpfs_indice(temp) - 1;
                        set_n_cpfs_indice(temp, total);
                        remover_registro(hf_ceps, cep_antigo);
                        inserir_registro(hf_ceps, cep_antigo, temp);
                    }
                }
            }
            free_indice_cep(temp);
        }
    }
    liberar_quadra(q);
    rip(morta);
}

void leQry(FILE* qry, Hashfile hf_quadra, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* svg, FILE* txt){
    char* linhaQry = malloc(tamLinha);
    char cep[12], cpf[20], nome[100], sobrenome[100], sexo, face,data[12], complemento[30], func[6];
    int num;
    while(fgets(linhaQry,tamLinha,qry)!=NULL){
        sscanf(linhaQry, "%s", func);
        if(strcmp(func,"rq")==0){
            sscanf(linhaQry, "%*s %s", cep);
            Quadra removida = malloc(SIZE_QUADRA);
            buscar_registro(hf_quadra, cep, removida);
            remover_quadra(hf_ceps, hf_pessoa, cep, txt);
            insere_X_ancora_svg(svg, removida);
        }
        else if(strcmp(func,"pq")==0){
            sscanf(linhaQry, "%*s %s", cep);
            pessoas_quadra(hf_ceps, hf_pessoa, hf_quadra, cep, svg);
        }
        else if(strcmp(func,"censo")==0){
            
        }
        else if(strcmp(func,"h?")==0){
            sscanf(linhaQry, "%*s %s", cpf);
            Pessoa procurada = malloc(SIZE_PESSOA);
            if(buscar_registro(hf_pessoa, cpf, procurada)){
                print_h_txt(txt, procurada);
            }
            rip(procurada);
        }
        else if(strcmp(func,"nasc")==0){
            sscanf(linhaQry, "%*s %s %s %s %c %s", cpf, nome ,sobrenome, &sexo, data);
            Pessoa nova = nascimento(cpf, nome, sobrenome, sexo, data);
            inserir_registro(hf_pessoa, cpf, nova);
            rip(nova);
        }
        else if(strcmp(func,"rip")==0){
            sscanf(linhaQry, "%*s %s",cpf);
            rip_pessoa(hf_pessoa, hf_ceps, hf_quadra,  cpf, svg, txt);
        }
        else if(strcmp(func,"mud")==0){
            sscanf(linhaQry,"%*s %s %s %c %d %s", cpf, cep, &face, &num, complemento);

        }
        else if(strcmp(func,"dspj")==0){

        }
    }
}