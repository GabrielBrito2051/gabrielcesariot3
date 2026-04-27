#ifndef geo_h
#define geo_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/quadra.h"
#include "../include/hashfile.h"

/*
    Esse modulo cuida da funcao de ler um arquivo de quadras .geo.

    A funcao leGeo le as linhas do arquivo .geo e vai criando e aramazenando os objetos lidos. Possui duas variaveis que sao passadas
    como referencia que armazenam as maiores coordenadas x e y das quadras.

    Alem disso, essa funcao insere os objetos criados num arquivo .svg.
*/

/// @brief Le o arquivo .geo e insere os dados no hashfile
/// @param geo Ponteiro para o arquivo geo
/// @param hf_quadra Hashfile das quadras
/// @param ts O estilo das quadras
/// @param svg Ponteiro para o arquivo svg
void leGeo(FILE* geo, Hashfile hf_quadra, Estilo ts, FILE* svg, int* max_x, int* max_y);

#endif