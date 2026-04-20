#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../unity/unity.h"
#include "../include/pm.h"
#include "../include/quadra.h"
#include "../include/hashfile.h"

Hashfile hf= NULL;
Hashfile hf_ceps = NULL;
FILE* pm = NULL;
FILE* txt = NULL;
int* total_hab, *total_mor, *total_hom, *total_mul, *mor_hom, *mor_mul;

void setUp() {
    pm = fopen("pmteste.pm", "r");
    hf = inicializar_hashfile("pmteste", SIZE_PESSOA);
    hf_ceps = inicializar_hashfile("indice-extra", SIZE_INDICE);
    txt = fopen("pmteste.txt", "w");
}

void tearDown() {
    fclose(pm);
    fclose(txt);
    fechar_hashfile(hf_ceps);
    fechar_hashfile(hf);
}

void test_lePm() {
    lePm(pm, hf, hf_ceps, txt, total_hab, total_mor, total_hom, total_mul, mor_hom, mor_mul);

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