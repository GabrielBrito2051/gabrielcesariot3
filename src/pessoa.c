#include "../include/pessoa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int morador, num;
    char nome[100], sobrenome[100], data[12], cpf[20], cep[16], complemento[30];
    char sexo, face;
}pessoa;

Pessoa nascimento(char* cpf, char* nome, char* sobrenome, char sexo, char* data){
    pessoa* novo = calloc(1, sizeof(pessoa));
    strcpy(novo->cpf,cpf);
    strcpy(novo->nome,nome);
    strcpy(novo->sobrenome,sobrenome);
    novo->sexo = sexo;
    strcpy(novo->data,data);
    novo->morador = 0;
    int num = -1;
    strcpy(novo->cep,"-1");
    novo->face = '0';
    strcpy(novo->complemento,"-1");

    return novo;
}

char* getCpfPessoa(Pessoa p){
    return ((pessoa*)p)->cpf;
}

char* getNome(Pessoa p){
    return ((pessoa*)p)->nome;
}

char* getSobrenome(Pessoa p){
    return((pessoa*)p)->sobrenome;
}

char getSexo(Pessoa p){
    return ((pessoa*)p)->sexo;
}

char* getData(Pessoa p){
    return ((pessoa*)p)->data;
}

int getMorador(Pessoa p){
    return ((pessoa*)p)->morador;
}

char* getCepMorador(Pessoa p){
    return ((pessoa*)p)->cep;
}

int getNum(Pessoa p){
    return ((pessoa*)p)->num;
}

char getFace(Pessoa p){
    return ((pessoa*)p)->face;
}

char* getComplemento(Pessoa p){
    return ((pessoa*)p)->complemento;
}

void setCpfPessoa(Pessoa p, char* cpf){
    strcpy(((pessoa*)p)->cpf,cpf);
}

void setNome(Pessoa p, char* nome){
    strcpy(((pessoa*)p)->nome, nome);
}

void setSobrenome(Pessoa p, char* sobrenome){
    strcpy(((pessoa*)p)->sobrenome,sobrenome);
}

void setSexo(Pessoa p, char sexo){
    ((pessoa*)p)->sexo = sexo;
}

void setMorador(Pessoa p, int morador){
    ((pessoa*)p)->morador = morador;
}

void setCepMorador(Pessoa p, char* cep){
    strcpy(((pessoa*)p)->cep,cep);
}

void setFace(Pessoa p, char face){
    ((pessoa*)p)->face = face;
}

void setNumero(Pessoa p ,int num){
     ((pessoa*)p)->num = num;
}

void setComplemento(Pessoa p, char* complemento){
    strcpy(((pessoa*)p)->complemento,complemento);
}

void rip(Pessoa p){
    free((pessoa*)p);
}