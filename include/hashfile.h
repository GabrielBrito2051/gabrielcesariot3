#ifndef hashfile_h
#define hashfile_h

#include <stdio.h>
#include <string.h>

typedef void* Registro;

/*
    Arquivo .h relacionado a estrutura de hashfile, com funcoes de inicializar, inserir e buscar um registro
*/

/// @brief Inicializa um novo hashfile
/// @param nome_dir O nome do diretorio
/// @param nome_buckets O nome do bucket
void inicializar_hashfile(char* nome_dir, char* nome_buckets);

/// @brief Insere uma informacao no registro
/// @param nome_dir O nome do diretorio
/// @param nome_buckets O nome do bucket
/// @param reg O registro que sera incluido no hashsfile
/// @return Retorna 1 se o registro foi inserido com sucesso e retorna 0 caso contrario
int inserir_registro(char* nome_dir, char* nome_buckets, Registro reg);

/// @brief Busca um determinado registro dentro do hashfile
/// @param n_dir O nome do diretorio
/// @param n_buck O nome do bucket
/// @param chave_buscada A chave do registro que estamos buscando
/// @return Retorna o registro buscado
Registro buscar_registro(char* n_dir, char* n_buck, int chave_buscada);

/// @brief Remove um registro do hashfile
/// @param n_dir O nome do diretorio
/// @param n_buck O nome do bucket
/// @param chave_removida A chave do registro que sera removido
/// @return Retorna 1 se o arquivo foi removido e 0 caso contrario
int remover_registro(char* n_dir, char* n_buck, int chave_removida);

#endif