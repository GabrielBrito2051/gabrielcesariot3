#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../unity/unity.h"
#include "../include/hashfile.h"

typedef struct {
    char cpf[17], nome[50];
    char sexo;
} Pessoa;

char* NOME_BASE_TESTE = "teste_db";

void setUp(void) {
    remove("teste_db_buckets.dat"); 
    remove("teste_db_dir.dat");
}

void tearDown(void) {
    remove("teste_db_buckets.dat"); 
    remove("teste_db_dir.dat");
}

void test_inicializar_e_fechar() {
    Hashfile hf = inicializar_hashfile((char*)NOME_BASE_TESTE, sizeof(Pessoa));
    
    TEST_ASSERT_NOT_NULL(hf);
    
    fechar_hashfile(hf);
}

void test_inserir_e_buscar() {
    Hashfile hf = inicializar_hashfile((char*)NOME_BASE_TESTE, sizeof(Pessoa));
    
    Pessoa inserir = {"111.222.333-44", "Milton Nascimento", 'M'};
    char* chave = inserir.cpf;

    int inseriu = inserir_registro(hf, chave, &inserir);
    TEST_ASSERT_EQUAL_INT(1, inseriu);

    Pessoa buscado;
    int encontrou = buscar_registro(hf, chave, &buscado);
    
    TEST_ASSERT_EQUAL_INT(1, encontrou);
    
    TEST_ASSERT_EQUAL_STRING("111.222.333-44", buscado.cpf);
    TEST_ASSERT_EQUAL_STRING("Milton Nascimento", buscado.nome);
    TEST_ASSERT_EQUAL_CHAR('M', buscado.sexo);

    fechar_hashfile(hf);
}

void test_buscar_registro_inexistente() {
    Hashfile hf = inicializar_hashfile(NOME_BASE_TESTE, sizeof(Pessoa));
    
    Pessoa buscado;
    int encontrou = buscar_registro(hf, "chave_fantasma", &buscado);
    
    TEST_ASSERT_EQUAL_INT(0, encontrou);

    fechar_hashfile(hf);
}

void test_remover_registro(void) {
    Hashfile hf = inicializar_hashfile((char*)NOME_BASE_TESTE, sizeof(Pessoa));
    
    Pessoa u1 = {"222.333.444-55", "Ana banana", 10.0};
    Pessoa u2 = {"333.444.555-66", "Mario Silva", 20.0};
    
    inserir_registro(hf, u1.cpf, &u1);
    inserir_registro(hf, u2.cpf, &u2);

    int removeu = remover_registro(hf, u1.cpf);
    TEST_ASSERT_EQUAL_INT(1, removeu);

    Pessoa buscado;
    int encontrou_u1 = buscar_registro(hf, u1.cpf, &buscado);
    TEST_ASSERT_EQUAL_INT(0, encontrou_u1);

    fechar_hashfile(hf);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_inicializar_e_fechar);
    RUN_TEST(test_inserir_e_buscar);
    RUN_TEST(test_buscar_registro_inexistente);
    RUN_TEST(test_remover_registro);

    return UNITY_END();
}