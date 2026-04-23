#ifndef geo_h
#define geo_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/quadra.h"
#include "../include/hashfile.h"

/*
    
*/

/// @brief Le o arquivo .geo e insere os dados no hashfile
/// @param geo Ponteiro para o arquivo geo
/// @param hf_quadra Hashfile das quadras
/// @param ts O estilo das quadras
/// @param svg Ponteiro para o arquivo svg
void leGeo(FILE* geo, Hashfile hf_quadra, Estilo ts, FILE* svg, int* max_x, int* max_y);

#endif