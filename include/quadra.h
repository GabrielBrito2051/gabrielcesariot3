#ifndef quadra_h
#define quadra_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_QUADRA 48
#define MAX_CPF 512
#define SIZE_INDICE 8208

typedef void* Quadra;
typedef void* Estilo;
typedef void* IndiceCep;

/*
    Uma quadra e um local onde os habitantes de bitnopolis podem morar. A quadra possui um cep, coordenadas x e y, comprimento e 
    largura.As quadras possuem um estilo, que e utilizado para a impressao delas no arquivo .svg. O estilo guarda as informacoes
    de sw, fill e strk. Existe tambem o indice de ceps, que guarda a qunatidade de moradores em uma determinada quadra.

    O cep possui uma quantidade maxima de caracteres, sendo ela 12. O sw possui uma quantidade maxima de caracteres de 8, e o fill e strk
    uma quantidade maxima de 30 caracteres. O indice de ceps pode armazenar no maximo 512 moradores por quadra.

    Para criar uma quadra, utiliza-se a funcao criar_quadra(), que aloca memoria para uma nova quadra. Para criar essa quadra, e
    necessario informar o cep, coordenadas x e y, largura e comprimento. Para criar um estilo, utiliza-se a funcao criar_estilo(). Que
    aloca memoria para um novo estilo de texto. Para realizar essa criacao, e necessario informar o sw, fill e strk. O mesmo vale para
    um indice de ceps, que, para ser criado, utiliza-se a funcao criar_indice_cep(), que aloca memoria para um novo indice de ceps. Para
    essa criacao, diferentemente das outras, nao e necessario informacoes, visto que o indice inicia-se vazio.
    
    Para cada um desses objetos descritos, existem funcoes getter e setters para obter e modificar suas informacoes.

    Finalmente, para remover uma quadra, utiliza-se a funcao liberar_quadra(), que, como o nome sugere, libera a memoria de uma quadra.
    Para liberar a memoria do estilo das quadras, utiliza-se a funcao removerEstilo(), e para remover um inidce de ceps, utiliza-se a 
    funcao free_indice_cep().
*/

/// @brief Cria uma nova quadra
/// @param cep O cep da quadra
/// @param x A coordenada x da ancora da quadra
/// @param y A coordenada y da ancora da quadra
/// @param w A largura da quadra
/// @param h A altura da quadra
/// @return Retorna um pornteiro para a quadra criada
Quadra criar_quadra(char* cep, double x, double y, double w, double h);

/// @brief Obtem o cep de uma quadra
/// @param q A quadra
/// @return Retorna uma string contendo o cep da quadra
char* getCepQuadra(Quadra q);

/// @brief Obtem o valor da coordenada x da ancora de uma quadra
/// @param q A quadra
/// @return Retorna o double contendo a coordenada x da quadra
double getXQuadra(Quadra q);

/// @brief Obtem o valor da coordenada y da ancora de uma quadra
/// @param q A quadra
/// @return Retorna a coordenada y da quadra
double getYQuadra(Quadra q);

/// @brief Obtem o valor da largura de uma quadra
/// @param q A quadra
/// @return Retorna a largura da quadra
double getWQuadra(Quadra q);

/// @brief Obtem o valor da altura de uma quadra
/// @param q A quadra
/// @return Retorna a altura da quadra
double getHQuadra(Quadra q);

/// @brief Define o cep de uma quadra
/// @param q A quadra
/// @param cep String contendo o novo cep da quadra
void setCepQuadra(Quadra q, char* cep);

/// @brief Define o valor da coordenada x da ancora de uma quadra
/// @param q A quadra
/// @param x O novo valor da coordenada x da ancora
void setXQuadra(Quadra q, double x);

/// @brief Define o valor da coordenada y da ancora de uma quadra
/// @param q A quadra
/// @param y O novo valor da coordenada y da ancora
void setYQuadra(Quadra q, double y);

/// @brief Define o valor da largura de uma quadra
/// @param q A quadra
/// @param w O novo valor da largura da quadra
void setWQuadra(Quadra q, double w);

/// @brief Define o valor da altura de uma quadra
/// @param q A quadra
/// @param h O novo valor da altura da quadra
void setHQuadra(Quadra q, double h);

/// @brief Libera a memoria de uma quadra
/// @param q A quadra
void liberar_quadra(Quadra q);

/// @brief Cria um novo estilo para a impressao das quadras no arquivo .svg
/// @param sw Espessura da borda da quadra
/// @param fill Cor de preenchimento da quadra
/// @param strk Cor da borda da quadra
/// @return Retorna um ponteiro para o estilo criado
Estilo criar_estilo(char* sw, char* fill, char* strk);

/// @brief Obtem o valor da espessura da borda das quadras
/// @param e O estilo
/// @return Retorna uma string contendo a espessura da borda das quadras
char* getSw(Estilo e);

/// @brief Obtem o valor da cor de preenchimento das quadras
/// @param e O estilo
/// @return Retorna uma string contendo a cor de preenchimento das quadras
char* getFill(Estilo e);

/// @brief Obtem o valor da cor da borda das quadras
/// @param e O estilo
/// @return Retorna uma string contendo a cor da borda das quadras
char* getStrk(Estilo e);

/// @brief Define o valor da espessura da borda das quadras
/// @param e O estilo
/// @param sw String contendo o novo valor da borda das quadras
void setSw(Estilo e, char* sw);

/// @brief Define o valor da cor de preenchimento das quadras
/// @param e O estilo
/// @param fill String contendo o novo valor da cor de preenchimento das quadras
void setFill(Estilo e, char* fill);

/// @brief Define o valor da cor de borda das quadras
/// @param e O estilo
/// @param strk String contendo o novo valor da cor de borda das quadras
void setStrk(Estilo e, char* strk);

/// @brief Libera a memoria do estilo
/// @param e O estilo
void removerEstilo(Estilo e);

/// @brief Cria um novo indice de ceps
/// @return Retorna o ponteiro para indice de ceps
IndiceCep criar_indice_cep();

/// @brief Obtem qual cep o indice esta armazenando
/// @param ic O indice de ceps
/// @return Retorna uma string com o cep que esta sendo armazenado
char* get_cep_indice(IndiceCep ic);

/// @brief Obtem o numero de cpfs em um determinado cep
/// @param ic O indice de ceps
/// @return Retorna o numero de cpfs
int get_n_cpfs_indice(IndiceCep ic);

/// @brief Obtem o cpf de um determinado elemento de um indice de ceps
/// @param ic O indice de ceps
/// @param indice A posicao do elemento que esta sendo buscado
/// @return Retorna a string com o cpf daquele elemento naquele cep
char* get_cpf_indice(IndiceCep ic, int indice);

/// @brief Define qual cep esta sendo armazenado pelo indice
/// @param ic O indice de ceps
/// @param cep String contendo o cep armazenado
void set_cep_indice(IndiceCep ic, char* cep);

/// @brief Define o numero de cpfs armazenados por um indice de ceps
/// @param ic O indice de ceps
/// @param n_cpfs O numero de cpfs no indice de ceps
void set_n_cpfs_indice(IndiceCep ic, int n_cpfs);

/// @brief Define o cpf de um elemento do indice de ceps
/// @param ic O indice de ceps
/// @param cpf O cpf do elemento
/// @param indice A posicao do elemento
void set_cpf_indice(IndiceCep ic, char* cpf, int indice);

/// @brief Libera a memoria de um indice de ceps
/// @param ic O indice de ceps
void free_indice_cep(IndiceCep ic);

#endif