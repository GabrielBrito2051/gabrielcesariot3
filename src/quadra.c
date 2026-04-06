#include "../include/quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* cep;
    double x, y, w, h;
}quadra;

typedef struct{
    char sw[8], fill[30], strk[30];
}estilo;

Quadra criar_quadra(char* cep, double x, double y, double w, double h){
    quadra* novo = malloc(sizeof(quadra));
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