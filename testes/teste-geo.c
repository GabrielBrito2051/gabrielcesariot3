#include "../unity/unity.h"
#include "../include/geo.h"
#include "../include/hashfile.h"
#include "../include/quadra.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* geo = NULL;
Estilo ts;
Hashfile hf = NULL;

void setUp(){
    geo = fopen("geoteste.geo", "r");
    ts = criar_estilo("1.0px", "gold", "MediumAquamarine");
    hf = inicializar_hashfile("geoteste", SIZE_QUADRA);
}

void tearDown(){
    fclose(geo);
    free(ts);
    fechar_hashfile(hf);
}

void test_leGeo(){
    leGeo(geo, hf, ts);

    Quadra q = malloc(SIZE_QUADRA);

    int encontrou = buscar_registro(hf, "b01.1", q);

    TEST_ASSERT_EQUAL_INT(1, encontrou);

    TEST_ASSERT_EQUAL_STRING("b01.1", getCepQuadra(q));
    TEST_ASSERT_EQUAL_INT(95, (int)getXQuadra(q));
    TEST_ASSERT_EQUAL_INT(95, (int)getYQuadra(q));
    TEST_ASSERT_EQUAL_INT(120, (int) getWQuadra(q));
    TEST_ASSERT_EQUAL_INT(80, (int) getHQuadra(q));

    remover_quadra(q);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(test_leGeo);

    return UNITY_END();
}