#ifndef qry_h
#define qry_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hashfile.h"
#include "../include/pessoa.h"
#include "../include/quadra.h"

/*

*/

/// @brief Faz a leitura do arquivo .qry
/// @param qry Ponteiro para o arquivo .qry
/// @param hf_quadra O hashfile que armazena quadras
/// @param hf_pessoa O hashfile que armazena pessoas
/// @param hf_ceps O hashfile que armazena o numero de pessoas por cep
/// @param svg Ponteiro para o arquivo .svg
/// @param txt Ponteiro para o arquivo .txt
void leQry(FILE* qry, Hashfile hf_quadra, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* svg, FILE* txt);

#endif