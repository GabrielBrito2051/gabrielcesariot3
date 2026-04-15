#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/pm.h"
#include "../include/hashfile.h"

#define tamLinha 256

void lePm(FILE* pm, Hashfile hf_pessoa){
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
            }
            rip(p);
        }
    }
    free(linhaPm);
}