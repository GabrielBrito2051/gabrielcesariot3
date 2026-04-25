#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/qry.h"
#include "../include/geo.h"
#include "../include/pm.h"
#include "../include/txt.h"
#include "../include/criarSvg.h"

#define PATH_LEN 512
#define FILE_NAME_LEN 256

void monta_caminho(char* destino, size_t tamanho_max, const char* dir, const char* arquivo) {
    if (strlen(dir) > 0) {
        if (dir[strlen(dir) - 1] == '/') {
            snprintf(destino, tamanho_max, "%s%s", dir, arquivo);
        } else {
            snprintf(destino, tamanho_max, "%s/%s", dir, arquivo);
        }
    } else {
        snprintf(destino, tamanho_max, "%s", arquivo);
    }
}

int main(int argc, char* argv[]) {
    char dirEntrada[PATH_LEN] = "";
    char dirSaida[PATH_LEN] = "";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    char nomeArquivoPm[FILE_NAME_LEN] = "";
    char onlyQry[FILE_NAME_LEN] = "";
    char baseQry[FILE_NAME_LEN] = "";
    char baseGeo[FILE_NAME_LEN] = "";
    char basePm[FILE_NAME_LEN] = "";
    int hasGeo = 0, hasSaida = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            strcpy(dirEntrada, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(dirSaida, argv[++i]);
            hasSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
            char *pNome = strrchr(nomeArquivoGeo, '/');
            strcpy(baseGeo, pNome ? pNome + 1 : nomeArquivoGeo);
            char *pExt = strrchr(baseGeo, '.');
            if (pExt && strcmp(pExt, ".geo") == 0) {
                *pExt = '\0';
            }
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoQry, argv[++i]);
            char *p = strrchr(argv[i], '/');
            strcpy(onlyQry, p ? p + 1 : argv[i]);
            char *pNome = strrchr(nomeArquivoQry, '/');
            strcpy(baseQry, pNome ? pNome + 1 : nomeArquivoQry);
            char *pExt = strrchr(baseQry, '.');
            if (pExt && strcmp(pExt, ".qry") == 0) {
                *pExt = '\0';
            }
        } else if (strcmp(argv[i], "-pm") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoPm, argv[++i]);
            char *pNome = strrchr(nomeArquivoPm, '/');
            strcpy(basePm, pNome ? pNome + 1 : nomeArquivoPm);
            char *pExt = strrchr(basePm, '.');
            if (pExt && strcmp(pExt, ".pm") == 0) {
                *pExt = '\0';
            }
        } else {
            fprintf(stderr, "Parametro desconhecido ou invalido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasGeo || !hasSaida) {
        fprintf(stderr, "Erro: parametros obrigatorios -f (geo) e -o (saida) nao fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[1024] = "";
    char fullPathPm[1024] = "";
    char fullPathQry[1024] = "";
    char arquivoSaidaSvgGeo[1024] = "";
    char arquivoSaidaSvgQry[1024] = "";
    char arquivoSaidaTxt[1024] = "";

    monta_caminho(fullPathGeo, sizeof(fullPathGeo), dirEntrada, nomeArquivoGeo);
    monta_caminho(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), dirSaida, baseGeo);
    strcat(arquivoSaidaSvgGeo, ".svg");

    if (strlen(nomeArquivoPm) > 0) {
        monta_caminho(fullPathPm, sizeof(fullPathPm), dirEntrada, nomeArquivoPm);
    }

    if (strlen(nomeArquivoQry) > 0) {
        monta_caminho(fullPathQry, sizeof(fullPathQry), dirEntrada, nomeArquivoQry);
        
        char baseNomeComposto[512];
        snprintf(baseNomeComposto, sizeof(baseNomeComposto), "%s-%s", baseGeo, baseQry);
        
        monta_caminho(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry), dirSaida, baseNomeComposto);
        strcat(arquivoSaidaSvgQry, ".svg");

        monta_caminho(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), dirSaida, baseNomeComposto);
        strcat(arquivoSaidaTxt, ".txt");
    }

    FILE* geo = fopen(fullPathGeo, "r");
    if (!geo) {
        fprintf(stderr, "Falha ao abrir arquivo geo: %s\n", fullPathGeo);
        return EXIT_FAILURE;
    }

    FILE* svgGeo = fopen(arquivoSaidaSvgGeo, "w");
    if (!svgGeo) {
        fprintf(stderr, "Falha ao criar arquivo svg geo: %s\n", arquivoSaidaSvgGeo);
        fclose(geo);
        return EXIT_FAILURE;
    }

    FILE* pm = NULL;
    if (strlen(fullPathPm) > 0) {
        pm = fopen(fullPathPm, "r");
        if (!pm) fprintf(stderr, "Aviso: Nao foi possivel abrir %s\n", fullPathPm);
    }

    FILE* qry = NULL;
    FILE* svgQry = NULL;
    FILE* txt = NULL;
    
    if (strlen(fullPathQry) > 0) {
        qry = fopen(fullPathQry, "r");
        svgQry = fopen(arquivoSaidaSvgQry, "w");
        txt = fopen(arquivoSaidaTxt, "w");
        
        if (!qry || !svgQry || !txt) {
            fprintf(stderr, "Falha ao criar ou abrir arquivos relacionados ao qry.\n");
        }
    }

    Hashfile hf_quadra = inicializar_hashfile("quadras", SIZE_QUADRA);
    Hashfile hf_pessoa = inicializar_hashfile("pessoas", SIZE_PESSOA);
    Hashfile hf_ceps = inicializar_hashfile("ceps", SIZE_INDICE);
    Estilo e = criar_estilo("1.0px", "green", "yellow");
    int total_hab = 0, total_mor = 0, total_hom = 0, total_mul = 0, mor_hom = 0, mor_mul = 0;
    int max_x=0, max_y=0;

    startSVG(svgGeo, max_x, max_y);
    leGeo(geo, hf_quadra, e, svgGeo, &max_x, &max_y);
    fechasvg(svgGeo);

    if (pm != NULL) {
        lePm(pm, hf_pessoa, hf_ceps, txt, &total_hab, &total_mor, &total_hom, &total_mul, &mor_hom, &mor_mul);
    }

    if (qry != NULL && svgQry != NULL && txt != NULL) {
        startSVG(svgQry, max_x, max_y);
        leQry(qry, hf_quadra, hf_pessoa, hf_ceps, svgQry, txt, &total_hab, &total_mor, &total_hom, &total_mul, &mor_hom, &mor_mul);
        desenha_quadras_svg(hf_quadra, svgQry, e);
        fechasvg(svgQry);
    }

    gerar_dump_hfd(hf_quadra, "quadras.hfd");
    gerar_dump_hfd(hf_pessoa, "pessoas.hfd");
    gerar_dump_hfd(hf_ceps, "ceps.hfd");

    if (geo) fclose(geo);
    if (svgGeo) fclose(svgGeo);
    if (pm) fclose(pm);
    if (qry) fclose(qry);
    if (svgQry) fclose(svgQry);
    if (txt) fclose(txt);

    fechar_hashfile(hf_ceps);
    fechar_hashfile(hf_pessoa);
    fechar_hashfile(hf_quadra);
    removerEstilo(e);

    return 0;
}