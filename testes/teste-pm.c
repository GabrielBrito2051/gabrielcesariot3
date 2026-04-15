#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../unity/unity.h"
#include "../include/pm.h"
#include "../include/hashfile.h"

Hashfile hf = NULL;
FILE* pm = NULL;

void setUp(void) {
    pm = fopen("pmteste.pm", "r");
    hf = inicializar_hashfile("pmteste", SIZE_PESSOA);
}

void tearDown(void) {
    fclose(pm);
    fechar_hashfile(hf);
}

void test_lePm() {
    lePm(pm, hf);

    Pessoa p = malloc(SIZE_PESSOA);
    int encontrou = buscar_registro(hf, "000.004.271-44", p);

    TEST_ASSERT_EQUAL_INT(1, encontrou);

    TEST_ASSERT_EQUAL_STRING("000.004.271-44", getCpfPessoa(p));
    TEST_ASSERT_EQUAL_STRING("Carien_Maayke", getNome(p));
    TEST_ASSERT_EQUAL_STRING("Giuliano_Moretti", getSobrenome(p));
    TEST_ASSERT_EQUAL_CHAR('M', getSexo(p));
    TEST_ASSERT_EQUAL_STRING("17/02/1966", getData(p));
    TEST_ASSERT_EQUAL_INT(1, getMorador(p));
    TEST_ASSERT_EQUAL_STRING("b07.4", getCepMorador(p));
    TEST_ASSERT_EQUAL_CHAR('O', getFace(p));
    TEST_ASSERT_EQUAL_INT(60, getNum(p));
    TEST_ASSERT_EQUAL_STRING("ap-1040", getComplemento(p));


    rip(p);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_lePm);
    
    return UNITY_END();
}