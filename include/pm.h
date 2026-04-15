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
void lePm(FILE* pm, Hashfile hf_pessoa);

#endif