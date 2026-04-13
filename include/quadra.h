#ifndef quadra_h
#define quadra_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_QUADRA 48

typedef void* Quadra;
typedef void* Estilo;

/*

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
void remover_quadra(Quadra q);

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

#endif