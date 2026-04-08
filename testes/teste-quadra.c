#include "../unity/unity.h"
#include "../include/quadra.h"
#include <stdlib.h>

Quadra q = NULL;
Estilo e = NULL;

void setUp() {
    q = criar_quadra("86050-000", 10.5, 20.5, 100.0, 50.0);
    e = criar_estilo("2.0", "red", "black");
}

void tearDown() {
    if (q != NULL) {
        remover_quadra(q);
        q = NULL;
    }
    
    if (e != NULL) {
        removerEstilo(e);
        e = NULL;
    }
}

void test_criar_quadra() {
    TEST_ASSERT_NOT_NULL(q);
}

void test_getters_quadra() {
    TEST_ASSERT_EQUAL_STRING("86050-000", getCepQuadra(q));
    
    TEST_ASSERT_EQUAL_DOUBLE(10.5, getXQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(20.5, getYQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(100.0, getWQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, getHQuadra(q));
}

void test_setters_quadra() {
    setCepQuadra(q, "86010-123");
    setXQuadra(q, 55.5);
    setYQuadra(q, 88.8);
    setWQuadra(q, 200.0);
    setHQuadra(q, 150.0);

    TEST_ASSERT_EQUAL_STRING("86010-123", getCepQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(55.5, getXQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(88.8, getYQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(200.0, getWQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(150.0, getHQuadra(q));
}

void test_criar_estilo() {
    TEST_ASSERT_NOT_NULL(e);
}

void test_getters_estilo() {
    TEST_ASSERT_EQUAL_STRING("2.0", getSw(e));
    TEST_ASSERT_EQUAL_STRING("red", getFill(e));
    TEST_ASSERT_EQUAL_STRING("black", getStrk(e));
}

void test_setters_estilo() {
    setSw(e, "5.5");
    setFill(e, "blue");
    setStrk(e, "white");

    TEST_ASSERT_EQUAL_STRING("5.5", getSw(e));
    TEST_ASSERT_EQUAL_STRING("blue", getFill(e));
    TEST_ASSERT_EQUAL_STRING("white", getStrk(e));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criar_quadra);
    RUN_TEST(test_getters_quadra);
    RUN_TEST(test_setters_quadra);

    RUN_TEST(test_criar_estilo);
    RUN_TEST(test_getters_estilo);
    RUN_TEST(test_setters_estilo);

    return UNITY_END();
}