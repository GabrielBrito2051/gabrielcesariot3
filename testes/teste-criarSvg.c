#include "../unity/unity.h"
#include "../include/criarSvg.h"
#include "../include/quadra.h"
#include <string.h>
#include <stdlib.h>

char buffer[1024 * 10]; 
FILE* temp;

void setUp() {
    memset(buffer, 0, sizeof(buffer));
    temp = fmemopen(buffer, sizeof(buffer), "w+");
}

void tearDown() {
    fclose(temp);
}

void test_startSVG_deve_escrever_tag_inicial() {
    startSVG(temp);
    fflush(temp);
    
    TEST_ASSERT_NOT_NULL(strstr(buffer, "<svg"));
}

void test_insere_quadra_svg_deve_formatar_corretamente() {
    Quadra q = criar_quadra("id1", 10, 10, 50, 50);
    Estilo e = criar_estilo("red", "blue", "2px");

    insere_quadra_svg(temp, q, e);
    fflush(temp);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<rect"));
    
    TEST_ASSERT_NOT_NULL(strstr(buffer, "fill:blue"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "stroke:2px"));
    
    TEST_ASSERT_NOT_NULL(strstr(buffer, "height=\"50.000000\""));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "width=\"50.000000\""));
    liberar_quadra(q);
    removerEstilo(e);
}

void test_fechasvg_deve_escrever_tag_final() {
    fechasvg(temp);
    fflush(temp);
    
    TEST_ASSERT_NOT_NULL(strstr(buffer, "</svg>"));
}

void test_insere_censo_svg_deve_conter_valores() {
    Quadra q = criar_quadra("q1", 0, 0, 100, 100);
    
    insere_censo_svg(temp, q, 10, 20, 30, 40);
    fflush(temp);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "10"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "20"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "30"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "40"));
    liberar_quadra(q);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_startSVG_deve_escrever_tag_inicial);
    RUN_TEST(test_insere_quadra_svg_deve_formatar_corretamente);
    RUN_TEST(test_insere_censo_svg_deve_conter_valores);
    RUN_TEST(test_fechasvg_deve_escrever_tag_final);
    return UNITY_END();
}