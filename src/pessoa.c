#include "../include/pessoa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int morador;
    char nome[100], sobrenome[100], data[12], cpf[17];
    char sexo;
}pessoa;

Pessoa nascimento(char* cpf, char* nome, char* sobrenome, char sexo, char* data){
    pessoa* novo = malloc(sizeof(pessoa));
    strcpy(novo->cpf,cpf);
    strcpy(novo->nome,nome);
    strcpy(novo->sobrenome,sobrenome);
    novo->sexo = sexo;
    strcpy(novo->data,data);
    novo->morador = 0;

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

void rip(Pessoa p){
    free((pessoa*)p);
}