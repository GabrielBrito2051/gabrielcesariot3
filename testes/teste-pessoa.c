#include "../unity/unity.h"
#include "../include/pessoa.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void setUp() {

}

void tearDown() {

}

void test_criacao_e_getters() {
    Pessoa p = nascimento("123456789", "Joao", "Gilberto", 'M', "15/04/1990");
    
    TEST_ASSERT_NOT_NULL(p);

    TEST_ASSERT_EQUAL_STRING("123456789", getCpfPessoa(p));
    
    TEST_ASSERT_EQUAL_STRING("Joao", getNome(p));
    TEST_ASSERT_EQUAL_STRING("Gilberto", getSobrenome(p));
    
    TEST_ASSERT_EQUAL_CHAR('M', getSexo(p));
    
    TEST_ASSERT_EQUAL_STRING("15/04/1990", getData(p));
    TEST_ASSERT_EQUAL_INT(0, getMorador(p));

    rip(p);
}

void test_setters() {
    Pessoa p = nascimento("111111111", "Ana", "Banana", 'F', "10/10/2000");
    TEST_ASSERT_NOT_NULL(p);

    setCpfPessoa(p, "999999999");
    setNome(p, "Maria");
    setSobrenome(p, "Silva");
    setSexo(p, 'F'); 
    setMorador(p, 1);

    TEST_ASSERT_EQUAL_STRING("999999999", getCpfPessoa(p));
    TEST_ASSERT_EQUAL_STRING("Maria", getNome(p));
    TEST_ASSERT_EQUAL_STRING("Silva", getSobrenome(p));
    TEST_ASSERT_EQUAL_CHAR('F', getSexo(p));
    TEST_ASSERT_EQUAL_INT(1, getMorador(p));

    rip(p);
}


int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criacao_e_getters);
    RUN_TEST(test_setters);

    return UNITY_END();
}