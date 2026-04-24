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
                if(getSexo(temp)=='M'){
                    (*mor_hom)--;
                }else{
                    (*mor_mul)--;
                }
                (*total_mor)--;
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
    Pessoa temp = calloc(1,SIZE_PESSOA);
    Quadra q = malloc(SIZE_QUADRA);
    int N=0, S=0, E=0, W=0;
    if(buscar_registro(hf_ceps, cep, procurado)){
        for(int i=0;i<get_n_cpfs_indice(procurado);i++){
            char* cpf_morador = get_cpf_indice(procurado, i);
            if(buscar_registro(hf_pessoa, cpf_morador, temp)){
                char face[9];
                strncpy(face, getFace(temp),8);
                face[8] = '\0';
                if(strcmp(face, "Face.N")==0 || strcmp(face, "N")==0){
                    N++;
                }
                else if(strcmp(face,"Face.S")==0 || strcmp(face, "S")==0){
                    S++;
                }
                else if(strcmp(face,"Face.L")==0 || strcmp(face,"Face.E")==0 || strcmp(face, "L")==0 || strcmp(face, "E")==0){
                    E++;
                }
                else if(strcmp(face,"Face.O")==0 || strcmp(face,"Face.W")==0 || strcmp(face, "O")==0 || strcmp(face, "W")==0){
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
    
    if (morta == NULL || q == NULL) {
        if (morta) rip(morta);
        if (q) liberar_quadra(q);
        return NULL;
    }

    if(buscar_registro(hf_pessoa, cpf, morta)){
        char cep_antigo[12];
        strcpy(cep_antigo, getCepMorador(morta));
        remover_registro(hf_pessoa, cpf);
        print_rip_txt(txt, morta);
        if(getMorador(morta)){
            IndiceCep temp = criar_indice_cep();
            if(buscar_registro(hf_quadra, cep_antigo, q)) {
                insere_rip_svg(svg, q, morta);
            } 
            if(buscar_registro(hf_ceps, cep_antigo, temp)){
                for(int i=0; i < get_n_cpfs_indice(temp); i++){
                    if(strcmp(get_cpf_indice(temp, i), cpf) == 0){
                        int ultimo = get_n_cpfs_indice(temp) - 1;
                        set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                        set_n_cpfs_indice(temp, ultimo);
                        remover_registro(hf_ceps, cep_antigo);
                        if(ultimo > 0) {
                            inserir_registro(hf_ceps, cep_antigo, temp);
                        }
                        break;
                    }
                }
            }
            free_indice_cep(temp);
        }
        liberar_quadra(q);
        return morta; 
    }
    
    liberar_quadra(q);
    rip(morta);
    return NULL;
}

Pessoa mud_pessoa(Hashfile hf_pessoa, Hashfile hf_ceps, char* cpf, char* cep, char* face, int num, char* complemento){
    Pessoa mudada = calloc(1,SIZE_PESSOA);
        if (mudada == NULL) {
        return NULL;
    }

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
            for(int i=0; i < get_n_cpfs_indice(temp); i++){
                if(strcmp(get_cpf_indice(temp, i), cpf) == 0){
                    int ultimo = get_n_cpfs_indice(temp) - 1;
                    set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                    set_n_cpfs_indice(temp, ultimo);
                    remover_registro(hf_ceps, cep_antigo);
                    
                    if(ultimo > 0) {
                        inserir_registro(hf_ceps, cep_antigo, temp);
                    }
                    break;
                }
            }
        }
        free_indice_cep(temp);

        IndiceCep temp_novo = criar_indice_cep();
        if(buscar_registro(hf_ceps, cep, temp_novo)) {
            int total_novo = get_n_cpfs_indice(temp_novo);
            set_cpf_indice(temp_novo, cpf, total_novo);
            set_n_cpfs_indice(temp_novo, total_novo + 1);
            remover_registro(hf_ceps, cep);
            inserir_registro(hf_ceps, cep, temp_novo);
        } else {
            set_cpf_indice(temp_novo, cpf, 0);
            set_n_cpfs_indice(temp_novo, 1);
            inserir_registro(hf_ceps, cep, temp_novo);
        }
        free_indice_cep(temp_novo);

        return mudada;
    }
    
    rip(mudada);
    return NULL;
}

Pessoa dspj_pessoa(Hashfile hf_pessoa, Hashfile hf_ceps, char* cpf){
    Pessoa despejada = malloc(SIZE_PESSOA);
    if (despejada == NULL) {
        return NULL;
    }

    if(buscar_registro(hf_pessoa, cpf, despejada)){
        setMorador(despejada, 0);
        remover_registro(hf_pessoa, cpf);
        inserir_registro(hf_pessoa, cpf, despejada);
        
        IndiceCep temp = criar_indice_cep();
        
        char cep_despejado[12];
        strcpy(cep_despejado, getCepMorador(despejada)); 
        if(buscar_registro(hf_ceps, cep_despejado, temp)){
            for(int i = 0; i < get_n_cpfs_indice(temp); i++){
                if(strcmp(get_cpf_indice(temp, i), cpf) == 0){
                    int ultimo = get_n_cpfs_indice(temp) - 1;
                    set_cpf_indice(temp, get_cpf_indice(temp, ultimo), i);
                    set_n_cpfs_indice(temp, ultimo);
                    remover_registro(hf_ceps, cep_despejado);

                    if(ultimo > 0) {
                        inserir_registro(hf_ceps, cep_despejado, temp);
                    }
                    break;
                }
            }
        }
        free_indice_cep(temp);
        return despejada;
    }
    
    rip(despejada);
    return NULL;
}

void leQry(FILE* qry, Hashfile hf_quadra, Hashfile hf_pessoa, Hashfile hf_ceps, FILE* svg, FILE* txt, int* total_hab, int* total_mor, int* total_hom, int* total_mul, int* mor_hom, int* mor_mul){
    char* linhaQry = malloc(tamLinha);
    char cep[12], cpf[20], nome[100], sobrenome[100], sexo, face[9],data[12], complemento[30], func[6];
    int num;
    while(fgets(linhaQry,tamLinha,qry)!=NULL){
        sscanf(linhaQry, "%s", func);
        if(strcmp(func,"rq")==0){
            sscanf(linhaQry, "%*s %s", cep);
            Quadra removida = malloc(SIZE_QUADRA);
            buscar_registro(hf_quadra, cep, removida);
            remover_quadra(hf_ceps, hf_pessoa, cep, txt, total_mor, mor_hom, mor_mul);
            insere_X_ancora_svg(svg, removida);
            liberar_quadra(removida);
            remover_registro(hf_quadra, cep);
        }
        else if(strcmp(func,"pq")==0){
            sscanf(linhaQry, "%*s %s", cep);
            pessoas_quadra(hf_ceps, hf_pessoa, hf_quadra, cep, svg);
        }
        else if(strcmp(func,"censo")==0){
            if(*total_hab>0){
                int ts = *total_hab - *total_mor;
                double mph, phh, phm, pmh, pmm, psh, psm;
                mph = (double)*total_mor / (double)*total_hab;
                phh = (double)*total_hom / (double)*total_hab;
                phm = (double)*total_mul / (double)*total_hab;
                pmh = (double)*mor_hom / (double)*total_hab;
                pmm = (double)*mor_mul / (double)*total_hab;
                psh = ((double)(*total_hom - *mor_hom)) / (double)ts;
                psm = ((double)(*total_mul - *mor_mul)) / (double)ts;
                print_censo_txt(txt, *total_hab, *total_mor, mph, *total_hom, *total_mul, phh, phm, pmh, pmm, ts, psh, psm);
            }
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
            if(getSexo(nova)=='M'){
                (*total_hom)++;
            }else{
                (*total_mul)++;
            }
            rip(nova);
            (*total_hab)++;
        }
        else if(strcmp(func,"rip")==0){
            sscanf(linhaQry, "%*s %s",cpf);
            Pessoa morta = rip_pessoa(hf_pessoa, hf_ceps, hf_quadra,  cpf, svg, txt);
            if(morta!=NULL){
                if(getSexo(morta)=='M'){
                    (*total_hom)--;
                    if(getMorador(morta)){
                        (*mor_hom)--;
                        (*total_mor)--;
                    }
                }else{
                    (*total_mul)--;
                    if(getMorador(morta)){
                        (*mor_mul)--;
                        (*total_mor)--;
                    }
                }
                (*total_hab)--;
                rip(morta);
            }
        }
        else if(strcmp(func,"mud")==0){
            sscanf(linhaQry,"%*s %s %s %s %d %s", cpf, cep, face, &num, complemento);
            Pessoa mudada = mud_pessoa(hf_pessoa, hf_ceps, cpf, cep, face, num, complemento);
            Quadra q = malloc(SIZE_QUADRA);
            buscar_registro(hf_quadra, cep, q);
            if(mudada!=NULL){
                insere_mud_svg(svg, q, mudada);
            }
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
            if(getSexo(despejada)=='M'){
                (*mor_hom)--;
            }else{
                (*mor_mul)--;
            }
            rip(despejada);
            (*total_mor)--;
        }
    }
    free(linhaQry);
}