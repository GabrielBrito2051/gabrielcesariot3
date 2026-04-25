#ifndef hashfile_h
#define hashfile_h

#include "../include/quadra.h"
#include <stddef.h>

typedef void* Hashfile;

/*
    Um hashfile extensivel e um arquivo binario que grava informacoes em disco, podendo ser expandido conforme necessario para
    reduzir o tempo gasto ao buscar informacoes gravadas.

    Um novo hashfle pode ser criado a partir da funcao inicializar_hashfile(), que cria dois arquivos distintos (.hf e .hfc). Para
    inicializar o hashfile, e necessario passar como parametro o tamanho das informacoes que vao ser guardadas. Cada hashfile 
    pode guarda somente um tipo de dado por vez, ou seja, caso existam dois ou mais tipos de dados diferentes, eles devem ser
    guardados em diferentes hashfiles.

    Informacoes podem ser gravadas, buscadas e removidas dentro do hashfile atraves das funcoes inserir_registro(),
    buscar_registro(), e remover_registro(), respectivamente. A chave utilizada para insercao e remocao consiste em uma string 
    alfanumerica, podendo conter no maximo 30 bytes.

    O hashfile pode ser fechado a partir da funcao fechar_hashfile(), e as informacoes permanecem gravadas nos arquivos .hf e .hfc.
*/

/// @brief Inicializa um novo hashfile
/// @param nome_base O nome do hashfile (sem extensao)
/// @param tamanho_registro O tamanho da struct em bytes
/// @return Retorna o hashfile aberto ou NULL em caso de erro
Hashfile inicializar_hashfile(char* nome_base, size_t tam_registro);

/// @brief Salva os dados, fecha os arquivos e libera a memoria de um hashfile
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

/// @brief Insere todas as quadras existentes no hashfile
/// @param hf_quadra O hashfile de quadras
/// @param svg Ponteiro para o arquivo .svg
/// @param e O estilo das quadras
void desenha_quadras_svg(Hashfile* hf_quadra, FILE* svg, Estilo e);

/// @brief Cria um arquivo de dump para um determinado hashfile
/// @param hf_ptr O hashfile que tera o dump criado
/// @param nome_arquivo_hfd Nome com extensao do arquivo de dump que sera criado
void gerar_dump_hfd(Hashfile* hf_ptr, char* nome_arquivo_hfd);

#endif