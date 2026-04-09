#ifndef hashfile_h
#define hashfile_h

#include <stddef.h>

typedef void* Hashfile;

/// @brief Inicializa um novo hashfile
/// @param nome_base O nome do hashfile (sem extensao)
/// @param tamanho_registro O tamanho da struct em bytes
/// @return Retorna o hashfile aberto ou NULL em caso de erro
Hashfile inicializar_hashfile(char* nome_base, size_t tam_registro);

/// @brief Salva os dados, fecha os arquivos e libera a memoria de um Hashfile
/// @param hf O hashfile
void fechar_hashfile(Hashfile hf);

/// @brief Insere um registro em um hashfile
/// @param hf O hashfile
/// @param chave A string que identifica o registro
/// @param dado Ponteiro para a struct que sera salva
/// @return 1 se inseriu com sucesso, 0 caso contrario
int inserir_registro(Hashfile hf, char* chave, void* dado);

/// @brief Busca um determinado registro dentro de um hashfile
/// @param hf O hashfile
/// @param chave_buscada A string que estamos buscando
/// @param dado_retorno Ponteiro onde o dado encontrado sera copiado
/// @return 1 se encontrou, 0 se nao encontrou
int buscar_registro(Hashfile hf, char* chave_buscada, void* dado_retorno);

/// @brief Remove um registro de um hashfile
/// @param hf O hashfile
/// @param chave_removida A string que será removida
/// @return 1 se removeu com sucesso, 0 caso contrario
int remover_registro(Hashfile hf, char* chave_removida);

#endif