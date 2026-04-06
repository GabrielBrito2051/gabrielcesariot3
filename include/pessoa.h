#ifndef pessoa_h
#define pessoa_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void* Pessoa;

/*
    Arquivo .h relacionado a uma pessoa, com funcoes de criar e remover uma pessoa, getters e setters
*/

/// @brief Cria uma nova pessoa
/// @param cpf O cpf da pessoa
/// @param nome O nome da pessoa
/// @param sobrenome O sobrenome da pessoa
/// @param sexo O sexo da pessoa
/// @param data A data de nascimento da pessoa
/// @return Retorna um ponteiro para a pessoa criada
Pessoa nascimento(char* cpf, char* nome, char* sobrenome, char sexo, char* data);

/// @brief Pega o cpf de uma pessoa
/// @param p A pessoa
/// @return Retorna um inteiro com cpf da pessoa
char* getCpfPessoa(Pessoa p);

/// @brief Obtem o nome de uma pessoa
/// @param p A pessoa
/// @return Retorna uma string com o nome da pessoa
char* getNome(Pessoa p);

/// @brief Pega o sobrenome de uma pessoa
/// @param p A pessoa
/// @return Retorna uma string com o sobreome da pessoa
char* getSobrenome(Pessoa p);

/// @brief Obtem o sexo de uma pessoa
/// @param p A pessoa
/// @return Retorna um caracter que indica o sexo da pessoa
char getSexo(Pessoa p);

/// @brief Pega a data de nascimento de uma pessoa
/// @param p A pessoa
/// @return Retorna uma string com a date de nascimento da pessoa
char* getData(Pessoa p);

/// @brief Verifica se uma pessoa tambem e um morador
/// @param p A pessoa
/// @return Retorna 1 se a pessoa possui uma propriedade e 0 caso contrario
int getMorador(Pessoa p);

/// @brief Define o cpf de uma pessoa
/// @param p A pessoa
/// @param cpf O novo cpf da pessoa
void setCpfPessoa(Pessoa p, char* cpf);

/// @brief Define o nome de uma pessoa
/// @param p A pessoa
/// @param nome O novo nome
void setNome(Pessoa p, char* nome);

/// @brief Define o sobrenome de uma pessoa
/// @param p A pessoa
/// @param sobrenome O novo sobrenome da pessoa
void setSobrenome(Pessoa p, char* sobrenome);

/// @brief Define o sexo da pessoa
/// @param p A pessoa
/// @param sexo O sexo da pessoa
void setSexo(Pessoa p, char sexo);

/// @brief Modifica o status de morador da pessoa
/// @param p A pessoa
/// @param morador 1 caso a pessoa passe a ter uma propriedade e 0 caso se torne morador de rua
void setMorador(Pessoa p, int morador);

/// @brief Libera a memoria de uma pessoa
/// @param p A pessoa
/// @return Retorna 1 se a memoria foi liberada com sucesso e 0 caso contrario
int rip(Pessoa p);

#endif