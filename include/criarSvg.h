#ifndef criarSvg_h
#define criarSvg_h

#include <stdio.h>
#include <stdlib.h>
#include "../include/quadra.h"
#include "../include/pessoa.h"

/*
    Esse modulo trata de arquivos .svg. Um arquivo .svg e um arquivo no qual e impresso formas geometricas, formando assim uma
    ilustracao.

    Para comecar a escrever num arquivo .svg, primeiro e necessario inicializa-lo, utilizando a funcao statrSVG().

    Nesse arquivo, e possivel inserir quadras, um 'X', inserir a quantidade de moradores em cada quadra, uma cruz no local de morte de
    um morador, um quadrado no local da mudanca de um morador e um cirulo no local de despejo de um morador.

    Antes de liberar o ponteiro e fechar o arquivo .svg, e necessario chamar a funcao fechaSVG() para inserir a tag final no arquivo. 
*/

/// @brief Adiciona a tag inicial do arquivo svg
/// @param svg Poneitro para o arquivo svg
/// @param max_x Valor que indica a maior coordenada x das quadras
/// @param max_y Valor que indica a maior coordenada y das quadras
void startSVG(FILE* svg, int max_x, int max_y);

/// @brief Insere uma quadra no arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra
/// @param e O estilo das quadras
void insere_quadra_svg(FILE *svg, Quadra q, Estilo e);

/// @brief Insere um X na ancora da quadra
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra
void insere_X_ancora_svg(FILE* svg, Quadra q);

/// @brief Insere o numero de moradores em cada face e o total de moradores no centro
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra
/// @param N A quantidade de pessoas na face norte
/// @param S A quantidade de pessoas na face sul
/// @param E A quantidade de pessoas na face leste
/// @param W A quantidade de pessoas na face oeste
void insere_censo_svg(FILE* svg, Quadra q, int N, int S, int E, int W);

/// @brief Insere uma cruz no local de morte de um morador
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra do morador
/// @param p O morador
void insere_rip_svg(FILE* svg, Quadra q, Pessoa p);

/// @brief Insere um quadrado no local de mudanca de um morador
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra do morador
/// @param p O morador
void insere_mud_svg(FILE* svg, Quadra q, Pessoa p);

/// @brief Insere um circulo no local de onde um morador foi despejado
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra do ex-morador
/// @param p O ex-morador
void insere_dspj_svg(FILE* svg, Quadra q, Pessoa p);

/// @brief Adiciona a tag final do arquivo svg
/// @param svg Ponteiro para o arquivo svg
void fechasvg(FILE* svg);

#endif