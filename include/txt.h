#ifndef txt_h
#define txt_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/quadra.h"
#include "../include/pessoa.h"

/*
    Esse modulo trata de arquivos .txt. Um arquivo .txt e um arquivo de texto que, nesse caso, guarda o log de informacoes dos comandos
    lidos no arquivo .qry.

    Nesse arquivo, e possivel inserir o cpf e o nome de pessoas que viraram sem-teto, inserir o censo da cidade, inserir o resultado da
    busca de um determinado morador, informar a morte de um habitante e insrir as informacoes de um despejo.
*/

/// @brief Imprime o cpf e o nome do morador que virou sem-teto
/// @param txt Ponteiro para o arquivo txt
/// @param p A pessoa
void print_rq_txt(FILE* txt, Pessoa p);

/// @brief Imprime as informacoes de bitnopoilis no arquivo .txt
/// @param txt Ponteiro para o arquivo .txt
/// @param th O total de habitantes
/// @param tm O total de moradores
/// @param mph A proporcao de moradores para habitantes
/// @param nh O numero de moradores homens
/// @param nm O numero de moradores mulheres
/// @param phh Porcentagem de habitantes homens
/// @param phm Porcentagem de habitantes mulheres
/// @param pmh Porcentagem de moradores homens
/// @param pmm Porcentagem de moradores mulheres
/// @param ts Total de sem-tetos
/// @param phs Porcentagem de homens sem-teto
/// @param pms Porcentagem de mulheres sem-teto
void print_censo_txt(FILE* txt, int th, int tm, double mph, int nh, int nm, double phh, double phm, double pmh, double pmm, int ts, double phs, double pms);

/// @brief Imprime as informacoes de uma determinada pessoa no arquivo .txt
/// @param txt Ponteiro para o arquivo .txt
/// @param p A pessoa
void print_h_txt(FILE* txt, Pessoa p);

/// @brief Imprime as informacoes de um falecido no arquivo .txt
/// @param txt Ponteiro para o arquivo .txt
/// @param p A pessoa
void print_rip_txt(FILE* txt, Pessoa p);

/// @brief Imprime as informacoes de um despejo no arquivo .txt
/// @param txt Ponteiro para o arquivo .txt
/// @param p A pessoa
void print_dspj_txt(FILE* txt, Pessoa p);

#endif