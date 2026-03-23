#include "../unity/unity.h"
#include "../include/hashfile.h"
#include <stdio.h>
#include <string.h>

char* dir_teste = "dir_teste.dat";
char* buck_teste = "buck_teste.dat";

void setUp(){
    inicializar_hashfile(dir_teste, buck_teste);
}

void tearDown(){
    remove(dir_teste);
    remove(buck_teste);
}

void teste_insercao_e_busca(){
    Registro reg = criar_registro(42, "ze-mane");

    int inseriu = inserir_registro(dir_teste, buck_teste, reg);
    TEST_ASSERT_EQUAL_INT(1, inseriu);

    Registro banco = buscar_registro(dir_teste, buck_teste, 42);

    TEST_ASSERT_NOT_NULL(banco);
    TEST_ASSERT_EQUAL_INT(42, get_chave_registro(banco));
    TEST_ASSERT_EQUAL_STRING("ze-mane", get_dado_reg(banco));

    free(banco);
}

void teste_remocao_registro(){
    Registro reg = criar_registro(99, "estrutura-de-dados");
    inserir_registro(dir_teste, buck_teste, reg);

    int removeu = remover_registro(dir_teste, buck_teste, 99);
    TEST_ASSERT_EQUAL_INT(1, removeu);

    Registro banco = buscar_registro(dir_teste, buck_teste, 99);
    TEST_ASSERT_NULL(banco);
}

void teste_insercao_com_split(){
    for(int i=0;i<40;i++){
        Registro temp = criar_registro(i, "testando");
        int inseriu = inserir_registro(dir_teste, buck_teste, temp);
        TEST_ASSERT_EQUAL_INT_MESSAGE(1, inseriu, "Falha na insercao durante o for");
    }
    Registro banco = buscar_registro(dir_teste,buck_teste, 35);
    TEST_ASSERT_NOT_NULL_MESSAGE(banco, "SUMIU!");
    TEST_ASSERT_EQUAL_INT(35, get_chave_registro(banco));

    if(banco) free(banco);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_insercao_e_busca);
    RUN_TEST(teste_remocao_registro);
    RUN_TEST(teste_insercao_com_split);

    return UNITY_END();
}