#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/geo.h"
#include "../include/hashfile.h"

#define tamLinha 256

void leGeo(FILE* geo, Hashfile hf_quadra, Estilo ts){
    char* linhaGeo = malloc(tamLinha);
    char cep[12], sw[8], fill[30], strk[30], func[3];
    double x, y, w, h;
    while(fgets(linhaGeo,tamLinha,geo)!=NULL){
        sscanf(linhaGeo,"%s", func);
        if(strcmp(func, "q")==0){
            sscanf(linhaGeo, "%*s %s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = criar_quadra(cep, x, y, w, h);
            if(!inserir_registro(hf_quadra, getCepQuadra(q), q)){
                printf("Falha ao inserir registro no hashfile");
            }
            liberar_quadra(q);
        }
        else if(strcmp(func, "cq")==0){
            sscanf(linhaGeo, "%*s %s %s %s", sw, fill, strk);
            setSw(ts, sw);
            setFill(ts, fill);
            setStrk(ts, strk);
        }
    }
    free(linhaGeo);
}