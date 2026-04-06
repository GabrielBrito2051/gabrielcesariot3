#include "../unity/unity.h"
#include "../include/pessoa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void setUp(void) {

}

void tearDown(void) {

}

void test_criacao_e_getters(void) {
    Pessoa p = nascimento(123456789, "Joao", "Gilberto", 'M', "15/04/1990");
    
    TEST_ASSERT_NOT_NULL(p);

    TEST_ASSERT_EQUAL_INT(123456789, getCpf(p));
    
    TEST_ASSERT_EQUAL_STRING("Joao", getNome(p));
    TEST_ASSERT_EQUAL_STRING("Gilberto", getSobrenome(p));
    
    TEST_ASSERT_EQUAL_CHAR('M', getSexo(p));
    
    TEST_ASSERT_EQUAL_STRING("15/04/1990", getData(p));
    TEST_ASSERT_EQUAL_INT(0, getMorador(p));

    rip(p);
}

void test_setters(void) {
    Pessoa p = nascimento(111111111, "Ana", "Banana", 'F', "10/10/2000");
    TEST_ASSERT_NOT_NULL(p);

    setCpf(p, 999999999);
    setNome(p, "Maria");
    setSobrenome(p, "Silva");
    setSexo(p, 'F'); 
    setMorador(p, 1);

    TEST_ASSERT_EQUAL_INT(999999999, getCpf(p));
    TEST_ASSERT_EQUAL_STRING("Maria", getNome(p));
    TEST_ASSERT_EQUAL_STRING("Silva", getSobrenome(p));
    TEST_ASSERT_EQUAL_CHAR('F', getSexo(p));
    TEST_ASSERT_EQUAL_INT(1, getMorador(p));

    rip(p);
}

void test_rip_destrutor(void) {
    Pessoa p = nascimento(123123123, "Chico", "Buarque", 'M', "01/01/1980");
    TEST_ASSERT_NOT_NULL(p);

    int resultado = rip(p);
    
    TEST_ASSERT_EQUAL_INT(1, resultado);
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_criacao_e_getters);
    RUN_TEST(test_setters);
    RUN_TEST(test_rip_destrutor);

    return UNITY_END();
}