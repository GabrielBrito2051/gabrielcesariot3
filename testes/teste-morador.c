#include "../unity/unity.h"
#include "../include/morador.h"
#include <stdlib.h>

Morador m = NULL;

void setUp(void) {
    m = criar_morador("111.222.333-44", "86000-000", 'N', 105, "Apto 42");
}

void tearDown(void) {
    if (m != NULL) {
        remover_morador(m);
    }
}

void test_criar_morador() {
    TEST_ASSERT_NOT_NULL(m);
}

void test_getters() {
    TEST_ASSERT_EQUAL_STRING("111.222.333-44", getCpfMorador(m));
    TEST_ASSERT_EQUAL_STRING("86000-000", getCepMorador(m));
    TEST_ASSERT_EQUAL_CHAR('N', getFace(m));
    TEST_ASSERT_EQUAL_INT(105, getNum(m));
    TEST_ASSERT_EQUAL_STRING("Apto 42", getComplemento(m));
}

void test_setters() {
    setCpfMorador(m, "999.888.777-66");
    setCepMorador(m, "86010-111");
    setFace(m, 'S');
    setNumero(m, 200);
    setComplemento(m, "Casa dos fundos");

    TEST_ASSERT_EQUAL_STRING("999.888.777-66", getCpfMorador(m));
    TEST_ASSERT_EQUAL_STRING("86010-111", getCepMorador(m));
    TEST_ASSERT_EQUAL_CHAR('S', getFace(m));
    TEST_ASSERT_EQUAL_INT(200, getNum(m));
    TEST_ASSERT_EQUAL_STRING("Casa dos fundos", getComplemento(m));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criar_morador);
    RUN_TEST(test_getters);
    RUN_TEST(test_setters);

    return UNITY_END();
}