#include <stdio.h>
#include <stdlib.h>
#include "../include/criarSvg.h"
#include "../include/quadra.h"
#include "../include/pessoa.h"

void startSVG(FILE* svg, int max_x, int max_y){
    if(max_x == 0 && max_y == 0){
         fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
    }else{
        fprintf(svg, "<svg viewBox=\"0 0 %d %d\" xmlns=\"http://www.w3.org/2000/svg\">\n", max_x + 51, max_y + 51);
    }
}

void insere_quadra_svg(FILE *svg, Quadra q, Estilo e){
    fprintf(svg, "<rect style=\"fill:%s;fill-opacity:0.5;stroke:%s;stroke-opacity:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" />\n",getFill(e), getStrk(e), getSw(e), getHQuadra(q), getWQuadra(q), getYQuadra(q), getXQuadra(q));
}

void insere_X_ancora_svg(FILE* svg, Quadra q){
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" style=\"font-family: 'Arial'; font-size: 24px; font-weight: bold; fill: red;\"> X </text>\n", getXQuadra(q)-6, getYQuadra(q)+12);
}

void insere_censo_svg(FILE* svg, Quadra q, int N, int S, int E, int W){
    int total = N + S + E + W;
    char* estiloFonte = "font-family: 'Arial'; font-size: 14px; fill: black;";
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" dominant-baseline=\"middle\" style=\"%s font-weight: bold; fill: blue;\">%d</text>\n", getXQuadra(q) + (getWQuadra(q) / 2.0), getYQuadra(q) + (getHQuadra(q) / 2.0), estiloFonte, total);
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" dominant-baseline=\"middle\" style=\"%s\">%d</text>\n",  getXQuadra(q) + (getWQuadra(q) / 2.0), getYQuadra(q) - 2, estiloFonte, S);
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" dominant-baseline=\"middle\" style=\"%s\">%d</text>\n",  getXQuadra(q) + (getWQuadra(q) / 2.0), getYQuadra(q) + getHQuadra(q) + 2, estiloFonte, N);
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" dominant-baseline=\"middle\" style=\"%s\">%d</text>\n", getXQuadra(q) - 2, getYQuadra(q) + (getHQuadra(q) / 2.0), estiloFonte, E);
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" text-anchor=\"middle\" dominant-baseline=\"middle\" style=\"%s\">%d</text>\n", getXQuadra(q) + getWQuadra(q) + 2, getYQuadra(q) + (getHQuadra(q) / 2.0), estiloFonte, W);
}

void insere_rip_svg(FILE* svg, Quadra q, Pessoa p){
    double x, y;
    if(strcmp(getFace(p), "Face.N")==0 || strcmp(getFace(p), "N")==0){
        x = getXQuadra(q) + getNum(p);
        y = getYQuadra(q) + getHQuadra(q);
    }
    else if(strcmp(getFace(p), "Face.S")==0 || strcmp(getFace(p), "S")==0){
        x = getXQuadra(q) + getNum(p);
        y = getYQuadra(q);
    }
    else if(strcmp(getFace(p), "Face.L")==0 || strcmp(getFace(p), "L")==0){
        x = getXQuadra(q);
        y = getYQuadra(q) + getNum(p);
    }
    else if(strcmp(getFace(p), "Face.O")==0 || strcmp(getFace(p), "O")==0){
        x = getXQuadra(q) + getWQuadra(q);
        y = getYQuadra(q) + getNum(p);
    }

    double x_vert = x - 2.5; 
    double y_vert = y - 10.0;
    
    double x_horiz = x - 10.0;
    double y_horiz = y - 2.5;

    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"3\" height=\"20\" style=\"fill:red; fill-opacity:1; stroke:red\" />\n", x_vert, y_vert+2);
    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"20\" height=\"3\" style=\"fill:red; fill-opacity:1; stroke:red\" />\n", x_horiz, y_horiz);
}

void insere_mud_svg(FILE* svg, Quadra q, Pessoa p){
    double x, y;
    if(strcmp(getFace(p), "Face.N")==0 || strcmp(getFace(p), "N")==0){
        x = getXQuadra(q) + getNum(p);
        y = getYQuadra(q) + getHQuadra(q);
    }
    else if(strcmp(getFace(p), "Face.S")==0 || strcmp(getFace(p), "S")==0){
        x = getXQuadra(q) + getNum(p);
        y = getYQuadra(q);
    }
    else if(strcmp(getFace(p), "Face.L")==0 || strcmp(getFace(p), "L")==0){
        x = getXQuadra(q);
        y = getYQuadra(q) + getNum(p);
    }
    else if(strcmp(getFace(p), "Face.O")==0 || strcmp(getFace(p), "O")==0){
        x = getXQuadra(q) + getWQuadra(q);
        y = getYQuadra(q) + getNum(p);
    }

    x -= 2.5;
    y -= 2.5;

    fprintf(svg, "<rect x=\"%lf\" y=\"%lf\" width=\"5\" height=\"5\" style=\"fill:red; fill-opacity:1; stroke:red\" />\n", x, y);
    fprintf(svg, "<text x=\"%lf\" y=\"%lf\" style=\"font-family: 'Arial'; font-size: 2px; font-weight: bold; fill: black;\"> %s </text>\n", getXQuadra(q)-9, getYQuadra(q), getCpfPessoa(p));
}

void insere_dspj_svg(FILE* svg, Quadra q, Pessoa p){
    double x, y;
    if(strcmp(getFace(p), "Face.N")==0 || strcmp(getFace(p), "N")==0){
        x = getXQuadra(q) + getNum(p);
        y = getYQuadra(q) + getHQuadra(q);
    }
    else if(strcmp(getFace(p), "Face.S")==0 || strcmp(getFace(p), "S")==0){
        x = getXQuadra(q) + getNum(p);
        y = getYQuadra(q);
    }
    else if(strcmp(getFace(p), "Face.L")==0 || strcmp(getFace(p), "L")==0){
        x = getXQuadra(q);
        y = getYQuadra(q) + getNum(p);
    }
    else if(strcmp(getFace(p), "Face.O")==0 || strcmp(getFace(p), "O")==0){
        x = getXQuadra(q) + getWQuadra(q);
        y = getYQuadra(q) + getNum(p);
    }

    fprintf(svg,"<circle cx=\"%lf\" cy=\"%lf\" r=\"7.5\" fill=\"black\" stroke=\"black\" stroke-width=\"2\"/>",x, y);
}

void fechasvg(FILE* svg){
    fprintf(svg,"</svg>\n");
}