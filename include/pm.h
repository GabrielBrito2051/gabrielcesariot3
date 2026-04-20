#ifndef pm_h
#define pm_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/pessoa.h"
#include "../include/hashfile.h"

/*

*/

/// @brief Le o arquivo .pm e insere os dados no hashfile
/// @param geo Ponteiro para o arquivo .pm
/// @param hf_pessoas O hashfile que armazena as pessoas
/// @param hf_ceps O hashfile que armazena ceps
/// @param txt Ponteiro para o arquivo .txt
/// @param total_hab Valor passado por referencia do contador de habitantes
/// @param total_mor Valor passado por referencia do contador de moradores
/// @param total_hom Valor passado por referencia do contador de homens
/// @param total_mul Valor passado por referencia do contador de mulheres
/// @param mor_hom Valor passado por referencia do contador de moradores homens
/// @param mor_mul Valor passado por referencia do contador de moradores mulheres
void lePm(FILE* pm, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* txt, int* total_hab, int* total_mor, int* total_hom, int* total_mul, int* mor_hom, int* mor_mul);

#endif