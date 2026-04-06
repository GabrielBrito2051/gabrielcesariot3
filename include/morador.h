#ifndef morador_h
#define morador_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void* Morador;

/*
    Arquivo .h relacionado a um morador, com funcoes de criar e remover um morador, getters e setters
*/

/// @brief Cria um novo morador
/// @param cpf String contendo o cpf do morador
/// @param cep String contendo o cep do morador
/// @param face Char contendo a face do morador
/// @param num Inteiro contendo o numero do morador
/// @param complemento String contendo o complemento do morador
/// @return Retorna um ponteiro para o morador criado
Morador criar_morador(char* cpf, char* cep, char face, int num, char* complemento);

/// @brief Obtem o cpf de um morador
/// @param m O morador
/// @return Retorna uma string contendo o cpf do morador
char* getCpfMorador(Morador m);

/// @brief Obtem o cep de um morador
/// @param m O morador
/// @return Retorna uma string contendo o cep do morador
char* getCepMorador(Morador m);

/// @brief Obtem a face de um morador
/// @param m O morador
/// @return Retorna um char de qual face o morador esta
char getFace(Morador m);

/// @brief Obtem o numero de um morador
/// @param m O morador
/// @return Retorna um int que representa o numero do morador
int getNum(Morador m);

/// @brief Obtem o complemento de um morador
/// @param m O morador
/// @return Retorna uma string contendo o complemento do morador
char* getComplemento(Morador m);

/// @brief Define o cpf do morador
/// @param m O morador
/// @param cpf String do novo cpf do morador
void setCpfMorador(Morador m, char* cpf);

/// @brief Define o cep de um morador
/// @param m O morador
/// @param cep String contendo o novo cep do morador
void setCepMorador(Morador m, char* cep);

/// @brief Define a face de um morador
/// @param m O morador
/// @param face Char da nova face do morador
void setFace(Morador m, char face);

/// @brief Define o numero do morador
/// @param m O morador
/// @param num Inteiro do novo numero do morador
void setNumero(Morador m ,int num);

/// @brief Define o complemento de um morador
/// @param m O morador
/// @param complemento String do novo complemento do morador 
void setComplemento(Morador m, char complemento);

/// @brief Libera a memoria de um morador
/// @param m O morador
/// @return Retorna 1 caso a memoria tenha sido liberada e 0 caso contrario
int remover_morador(Morador m);

#endif