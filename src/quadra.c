#include "../include/quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char cep[12];
    double x, y, w, h;
}quadra;

typedef struct{
    char sw[8], fill[30], strk[30];
}estilo;

typedef struct{
    char cep[12];
    int n_cpf;
    char cpfs[MAX_CPF][16];
}indicecep;

Quadra criar_quadra(char* cep, double x, double y, double w, double h){
    quadra* novo = calloc(1, sizeof(quadra));
    strcpy(novo->cep,cep);
    novo->x = x;
    novo->y = y;
    novo->w = w;
    novo->h = h;

    return novo;
}

char* getCepQuadra(Quadra q){
    return ((quadra*)q)->cep;
}

double getXQuadra(Quadra q){
    return ((quadra*)q)->x;
}

double getYQuadra(Quadra q){
    return ((quadra*)q)->y;
}

double getWQuadra(Quadra q){
    return ((quadra*)q)->w;
}

double getHQuadra(Quadra q){
    return ((quadra*)q)->h;
}

void setCepQuadra(Quadra q, char* cep){
    strcpy(((quadra*)q)->cep,cep);
}

void setXQuadra(Quadra q, double x){
    ((quadra*)q)->x = x;
}

void setYQuadra(Quadra q, double y){
    ((quadra*)q)->y = y;
}

void setWQuadra(Quadra q, double w){
    ((quadra*)q)->w = w;
}

void setHQuadra(Quadra q, double h){
    ((quadra*)q)->h = h;
}

void liberar_quadra(Quadra q){
    free((quadra*)q);
}

Estilo criar_estilo(char* sw, char* fill, char* strk){
    estilo* novo = malloc(sizeof(estilo));
    strcpy(novo->sw,sw);
    strcpy(novo->fill,fill);
    strcpy(novo->strk,strk);

    return novo;
}

char* getSw(Estilo e){
    return ((estilo*)e)->sw;
}

char* getFill(Estilo e){
    return ((estilo*)e)->fill;
}

char* getStrk(Estilo e){
    return ((estilo*)e)->strk;
}

void setSw(Estilo e, char* sw){
    strcpy(((estilo*)e)->sw,sw);
}

void setFill(Estilo e, char* fill){
    strcpy(((estilo*)e)->fill,fill);
}

void setStrk(Estilo e, char* strk){
    strcpy(((estilo*)e)->strk,strk);
}

void removerEstilo(Estilo e){
    free((estilo*)e);
}

IndiceCep criar_indice_cep(){
    indicecep* novo = calloc(1,sizeof(indicecep));
    novo->n_cpf = 0;
    return novo;
}

char* get_cep_indice(IndiceCep ic){
    return((indicecep*)ic)->cep;
}

int get_n_cpfs_indice(IndiceCep ic){
    return((indicecep*)ic)->n_cpf;
}

char* get_cpf_indice(IndiceCep ic, int indice){
    return((indicecep*)ic)->cpfs[indice];
}

void set_cep_indice(IndiceCep ic, char* cep){
    strcpy(((indicecep*)ic)->cep,cep);
}

void set_n_cpfs_indice(IndiceCep ic, int n_cpfs){
    ((indicecep*)ic)->n_cpf = n_cpfs;
}

void set_cpf_indice(IndiceCep ic, char* cpf, int indice){
    strcpy(((indicecep*)ic)->cpfs[indice], cpf);
}

void free_indice_cep(IndiceCep ic){
    free((indicecep*)ic);
}