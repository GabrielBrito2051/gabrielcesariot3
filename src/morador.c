#include "../include/morador.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int num;
    char cpf[15], cep[10], face, complemento[10];
}morador;

Morador criar_morador(char* cpf, char* cep, char face, int num, char* complemento){
    morador* novo = malloc(sizeof(morador));
    strcpy(novo->cpf,cpf);
    strcpy(novo->cep,cep);
    novo->face = face;
    novo->num = num;
    strcpy(novo->complemento,complemento);

    return novo;
}

char* getCpfMorador(Morador m){
    return ((morador*)m)->cpf;
}

char* getCepMorador(Morador m){
    return ((morador*)m)->cep;
}

char getFace(Morador m){
    return ((morador*)m)->face;
}

int getNum(Morador m){
    return ((morador*)m)->num;
}

char* getComplemento(Morador m){
    return ((morador*)m)->complemento;
}

void setCpfMorador(Morador m, char* cpf){
    strcpy(((morador*)m)->cpf,cpf);
}

void setCepMorador(Morador m, char* cep){
    strcpy(((morador*)m)->cep,cep);
}

void setFace(Morador m, char face){
    ((morador*)m)->face = face;
}

void setNumero(Morador m ,int num){
     ((morador*)m)->num = num;
}

void setComplemento(Morador m, char* complemento){
    strcpy(((morador*)m)->complemento,complemento);
}

void remover_morador(Morador m){
    free((morador*)m);
}