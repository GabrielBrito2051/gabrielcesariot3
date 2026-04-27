#ifndef qry_h
#define qry_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hashfile.h"
#include "../include/pessoa.h"
#include "../include/quadra.h"

/*
    Esse modulo cuida da funcao de ler o arquivo de comandos .qry.

    A funcao leQry le as linhas do arquivo .qry e realiza os comandos que sao lidos em cada linha. Para os comandos, sao necessarias 6
    variaveis que guardam o total de habitantes, total de moradores, total de habitantes homens, total de habitantes mulheres, total de
    moradores homens e total de moradores mulheres.

    Alem disso, essa funcao tambem insere as informacoes do que esta ocorrendo nos comandos em arquivos de texto e tambem em
    arquivos .svg.
*/

/// @brief Faz a leitura do arquivo .qry
/// @param qry Ponteiro para o arquivo .qry
/// @param hf_quadra O hashfile que armazena quadras
/// @param hf_pessoa O hashfile que armazena pessoas
/// @param hf_ceps O hashfile que armazena o numero de pessoas por cep
/// @param svg Ponteiro para o arquivo .svg
/// @param txt Ponteiro para o arquivo .txt
/// @param total_hab Valor passado por referencia do contador de habitantes
/// @param total_mor Valor passado por referencia do contador de moradores
/// @param total_hom Valor passado por referencia do contador de homens
/// @param total_mul Valor passado por referencia do contador de mulheres
/// @param mor_hom Valor passado por referencia do contador de moradores homens
/// @param mor_mul Valor passado por referencia do contador de moradores mulheres
void leQry(FILE* qry, Hashfile hf_quadra, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* svg, FILE* txt,  int* total_hab, int* total_mor, int* total_hom, int* total_mul, int* mor_hom, int* mor_mul);

#endif