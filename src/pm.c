#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/pm.h"
#include "../include/hashfile.h"
#include "../include/quadra.h"

#define tamLinha 256

void inserir_morador_no_cep(Hashfile hf_ceps, char* cep_alvo, char* cpf_novo, FILE* txt){
    IndiceCep temp = criar_indice_cep();
    if(buscar_registro(hf_ceps, cep_alvo, temp)){
        if(get_n_cpfs_indice(temp)<MAX_CPF){
            set_cpf_indice(temp, cpf_novo, get_n_cpfs_indice(temp));
            set_n_cpfs_indice(temp, get_n_cpfs_indice(temp)+1);
            remover_registro(hf_ceps, cep_alvo);
            inserir_registro(hf_ceps, cep_alvo, temp);
        }else{
            fprintf(txt, "A quadra %s esta cheia!", get_cep_indice(temp));
        }
    }else{
        set_cep_indice(temp, cep_alvo);
        set_n_cpfs_indice(temp, 1);
        set_cpf_indice(temp, cpf_novo, 0);
        inserir_registro(hf_ceps, cep_alvo, temp);
    }
    free_indice_cep(temp);
}

void lePm(FILE* pm, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* txt){
    char* linhaPm = malloc(tamLinha);
    int morador, num;
    char nome[100], sobrenome[100], data[12], cpf[20], cep[16], complemento[30];
    char sexo, face;
    char func;
    while(fgets(linhaPm, tamLinha, pm)!=NULL){
        sscanf(linhaPm, "%c", &func);
        if(func == 'p'){
            sscanf(linhaPm, "%*s %s %s %s %c %s ", cpf, nome, sobrenome, &sexo, data);
            Pessoa p = nascimento(cpf, nome, sobrenome, sexo, data);
            if(!inserir_registro(hf_pessoa, cpf, p)){
                printf("Falha ao inserir uma pessoa no hashfile");
            }
            rip(p);
        }
        else if(func=='m'){
            sscanf(linhaPm, "%*s %s %s %c %d %s", cpf, cep, &face, &num, complemento);
            Pessoa p = malloc(SIZE_PESSOA);
            int encontrou = buscar_registro(hf_pessoa, cpf, p);
            if(!encontrou){
                printf("\n\n---Falha ao encotrar a pessoa que iria se tornar morador---\n\n");
            }else{
                remover_registro(hf_pessoa, cpf);   
                setMorador(p, 1);
                setCepMorador(p, cep);
                setFace(p, face);
                setNumero(p, num);
                setComplemento(p, complemento);
                inserir_registro(hf_pessoa, cpf, p);
                inserir_morador_no_cep(hf_ceps, cep, cpf, txt);
            }
            rip(p);
        }
    }
    free(linhaPm);
}