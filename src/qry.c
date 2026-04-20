#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/hashfile.h"
#include "../include/pessoa.h"
#include "../include/quadra.h"
#include "../include/criarSvg.h"
#include "../include/txt.h"

#define tamLinha 256

void remover_quadra(Hashfile hf_ceps, Hashfile hf_pessoa, char* cep_destruido, FILE* txt,  int* total_mor, int* mor_hom, int* mor_mul){
    IndiceCep alvo = criar_indice_cep();
    Pessoa temp = malloc(SIZE_PESSOA);
    if(buscar_registro(hf_ceps, cep_destruido, alvo)){
        for(int i = 0;i<get_n_cpfs_indice(alvo);i++){
            char* cpf_morador = get_cpf_indice(alvo, i);
            if(buscar_registro(hf_pessoa, cpf_morador, temp)){
                setMorador(temp, 0);
                if(getSexo(temp)=='H'){
                    mor_hom--;
                }else{
                    mor_mul--;
                }
                total_mor--;
                remover_registro(hf_pessoa, cpf_morador);
                inserir_registro(hf_pessoa, cpf_morador, temp);
                print_rq_txt(txt, temp);
            }
        }
        remover_registro(hf_ceps, cep_destruido);
    }
    free_indice_cep(alvo);
    rip(temp);
}

void pessoas_quadra(Hashfile hf_ceps, Hashfile hf_pessoa, Hashfile hf_quadra, char* cep, FILE* svg){
    IndiceCep procurado = criar_indice_cep();
    Pessoa temp = malloc(SIZE_PESSOA);
    Quadra q = malloc(SIZE_QUADRA);
    int N=0, S=0, E=0, W=0;
    if(buscar_registro(hf_ceps, cep, procurado)){
        for(int i=0;i<get_n_cpfs_indice(procurado);i++){
            char* cpf_morador = get_cpf_indice(procurado, i);
            if(buscar_registro(hf_pessoa, cpf_morador, temp)){
                char face = getFace(temp);
                if(face=='N'){
                    N++;
                }
                else if(face=='S'){
                    S++;
                }
                else if(face=='L' || face=='E'){
                    E++;
                }
                else if(face=='O' || face=='W'){
                    W++;
                }
            }
        }
        if(buscar_registro(hf_quadra, cep, q)){
            insere_censo_svg(svg, q, N, S, E, W);
        }
    }
    rip(temp);
    liberar_quadra(q);
    free_indice_cep(procurado);
}

Pessoa rip_pessoa(Hashfile hf_pessoa, Hashfile hf_ceps, Hashfile hf_quadra, char*cpf, FILE* svg, FILE* txt){
    Pessoa morta = malloc(SIZE_PESSOA);
    Quadra q = malloc(SIZE_QUADRA);
    if(buscar_registro(hf_pessoa, cpf, morta)){
        char cep_antigo[12];
        strcpy(cep_antigo, getCepMorador(morta));
        remover_registro(hf_pessoa, cpf);
        print_rip_txt(txt, morta);
        if(getMorador(morta)){
            IndiceCep temp = criar_indice_cep();
            buscar_registro(hf_quadra, cep_antigo, q);
            insere_rip_svg(svg, q, morta);
            if(buscar_registro(hf_ceps, cep_antigo, temp)){
                for(int i=0;i<get_n_cpfs_indice(temp);i++){
                    if(strcmp(get_cpf_indice(temp, i), cpf)==0){
                        int ultimo = get_n_cpfs_indice(temp) - 1;
                        set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                        int total = get_n_cpfs_indice(temp) - 1;
                        set_n_cpfs_indice(temp, total);
                        remover_registro(hf_ceps, cep_antigo);
                        inserir_registro(hf_ceps, cep_antigo, temp);
                    }
                }
            }
            free_indice_cep(temp);
        }
    }
    liberar_quadra(q);
    return morta;
}

Pessoa mud_pessoa(Hashfile hf_pessoa, Hashfile hf_ceps, char* cpf, char* cep, char face, int num, char* complemento){
    Pessoa mudada = malloc(SIZE_PESSOA);
    if(buscar_registro(hf_pessoa, cpf, mudada)){
        char cep_antigo[12];
        strcpy(cep_antigo, getCepMorador(mudada));
        setCepMorador(mudada, cep);
        setFace(mudada, face);
        setNumero(mudada, num);
        setComplemento(mudada, complemento);
        remover_registro(hf_pessoa, cpf);
        inserir_registro(hf_pessoa, cpf, mudada);
        IndiceCep temp = criar_indice_cep();
        if(buscar_registro(hf_ceps, cep_antigo, temp)){
            for(int i=0;i<get_n_cpfs_indice(temp);i++){
                if(strcmp(get_cpf_indice(temp, i),cpf)==0){
                    int ultimo = get_n_cpfs_indice(temp) - 1;
                    set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                    int total = get_n_cpfs_indice(temp) - 1;
                    set_n_cpfs_indice(temp, total);
                    remover_registro(hf_ceps, cep_antigo);
                    inserir_registro(hf_ceps, cep_antigo, temp);
                }
            }
        }
        free_indice_cep(temp);
    }
    return mudada;
}

Pessoa dspj_pessoa(Hashfile hf_pessoa, Hashfile hf_ceps, char* cpf){
    Pessoa despejada = malloc(SIZE_PESSOA);
    if(buscar_registro(hf_pessoa, cpf, despejada)){
        setMorador(despejada, 0);
        remover_registro(hf_pessoa, cpf);
        inserir_registro(hf_pessoa, cpf, despejada);
        IndiceCep temp = criar_indice_cep();
        if(buscar_registro(hf_ceps, getCepMorador(despejada), temp)){
            for(int i=0;i<get_n_cpfs_indice(temp);i++){
                if(strcmp(get_cpf_indice(temp, i),cpf)==0){
                    int ultimo = get_n_cpfs_indice(temp) - 1;
                    set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                    int total = get_n_cpfs_indice(temp) - 1;
                    set_n_cpfs_indice(temp, total);
                    remover_registro(hf_ceps, getCepMorador(despejada));
                    inserir_registro(hf_ceps, getCepMorador(despejada), temp);
                }
            }
        }
        free_indice_cep(temp);
    }
    return despejada;
}

void leQry(FILE* qry, Hashfile hf_quadra, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* svg, FILE* txt, int* total_hab, int* total_mor, int* total_hom, int* total_mul, int* mor_hom, int* mor_mul){
    char* linhaQry = malloc(tamLinha);
    char cep[12], cpf[20], nome[100], sobrenome[100], sexo, face,data[12], complemento[30], func[6];
    int num;
    while(fgets(linhaQry,tamLinha,qry)!=NULL){
        sscanf(linhaQry, "%s", func);
        if(strcmp(func,"rq")==0){
            sscanf(linhaQry, "%*s %s", cep);
            Quadra removida = malloc(SIZE_QUADRA);
            buscar_registro(hf_quadra, cep, removida);
            remover_quadra(hf_ceps, hf_pessoa, cep, txt, total_mor, mor_hom, mor_mul);
            insere_X_ancora_svg(svg, removida);
        }
        else if(strcmp(func,"pq")==0){
            sscanf(linhaQry, "%*s %s", cep);
            pessoas_quadra(hf_ceps, hf_pessoa, hf_quadra, cep, svg);
        }
        else if(strcmp(func,"censo")==0){
            int ts = *total_hab - *total_mor;
            double mph, phh, phm, pmh, pmm, psh, psm;
            mph = (double)*total_mor / (double)*total_hab * 100;
            phh = (double)*total_hom / (double)*total_hab *100;
            phm = (double)*total_mul / (double)*total_hab * 100;
            pmh = (double)*mor_hom / (double)*total_hab * 100;
            pmm = (double)*mor_mul / (double)*total_hab * 100;
            psh = ((double)(*total_hom - *mor_hom)) / (double)*total_hab * 100;
            psm = ((double)(*total_mul - *mor_mul)) / (double)*total_hab * 100;
            print_censo_txt(txt, *total_hab, *total_mor, mph, *total_hom, *total_mor, phh, phm, pmh, pmm, ts, psh, psm);
        }
        else if(strcmp(func,"h?")==0){
            sscanf(linhaQry, "%*s %s", cpf);
            Pessoa procurada = malloc(SIZE_PESSOA);
            if(buscar_registro(hf_pessoa, cpf, procurada)){
                print_h_txt(txt, procurada);
            }
            rip(procurada);
        }
        else if(strcmp(func,"nasc")==0){
            sscanf(linhaQry, "%*s %s %s %s %c %s", cpf, nome ,sobrenome, &sexo, data);
            Pessoa nova = nascimento(cpf, nome, sobrenome, sexo, data);
            inserir_registro(hf_pessoa, cpf, nova);
            if(getSexo(nova)=='H'){
                total_hom++;
            }else{
                total_mul++;
            }
            rip(nova);
            *total_hab++;
        }
        else if(strcmp(func,"rip")==0){
            sscanf(linhaQry, "%*s %s",cpf);
            Pessoa morta = rip_pessoa(hf_pessoa, hf_ceps, hf_quadra,  cpf, svg, txt);
            if(getSexo(morta)=='M'){
                *total_hom--;
                if(getMorador(morta)){
                    *mor_hom--;
                    *total_mor--;
                }
            }else{
                *total_mul--;
                if(getMorador(morta)){
                    *mor_mul--;
                    *total_mor--;
                }
            }
            *total_hab--;
        }
        else if(strcmp(func,"mud")==0){
            sscanf(linhaQry,"%*s %s %s %c %d %s", cpf, cep, &face, &num, complemento);
            Pessoa mudada = mud_pessoa(hf_pessoa, hf_ceps, cpf, cep, face, num, complemento);
            Quadra q = malloc(SIZE_QUADRA);
            buscar_registro(hf_quadra, cep, q);
            insere_mud_svg(svg, q, mudada);
            rip(mudada);
            liberar_quadra(q);
        }
        else if(strcmp(func,"dspj")==0){
            sscanf(linhaQry, "%*s %s", cpf);
            Pessoa despejada = dspj_pessoa(hf_pessoa, hf_ceps, cpf);
            Quadra q = malloc(SIZE_QUADRA);
            if(buscar_registro(hf_quadra, getCepMorador(despejada), q)){
                print_dspj_txt(txt, despejada);
                insere_dspj_svg(svg,q, despejada);
            }
            liberar_quadra(q);
            if(getSexo(despejada)=='H'){
                *mor_hom--;
            }else{
                *mor_mul--;
            }
            rip(despejada);
            *total_mor--;
        }
    }
}