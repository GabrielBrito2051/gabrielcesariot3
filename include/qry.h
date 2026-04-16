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


void leQry(FILE* qry, Hashfile hf_quadra, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* svg, FILE* txt);

#endif