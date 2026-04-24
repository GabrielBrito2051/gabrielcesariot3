#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/txt.h"
#include "../include/quadra.h"
#include "../include/pessoa.h"

void print_rq_txt(FILE* txt, Pessoa p){
    fprintf(txt,"Morador:%s %s\tCpf:%s virou sem-teto\n", getNome(p), getSobrenome(p), getCpfPessoa(p));
}

void print_censo_txt(FILE* txt, int th, int tm, double mph, int nh, int nm, double phh, double phm, double pmh, double pmm, int ts, double phs, double pms){
    fprintf(txt, "Total de habitantes: %d, Total de moradores: %d, Relacao morador/habitante: %lf\n", th, tm, mph);
    fprintf(txt, "Total de homens: %d, Total de mulheres: %d, Porcentagem da populacao homem: %lf, Porcentagem da populacao mulher: %lf\n", nh, nm, phh, phm);
    fprintf(txt, "Porcentagem de moradores homens: %lf, Porcentagem de moradores mulheres: %lf\n", pmh, pmm);
    fprintf(txt, "Total de sem-tetos: %d, Porcentagem de sem-tetos homens: %lf, Porcentagem de sem-tetos mulheres: %lf\n\n", ts, phs, pms);
}

void print_h_txt(FILE* txt, Pessoa p){
    fprintf(txt, "Cpf: %s\nNome: %s %s Sexo: %c Dia de nasciento: %s - ", getCpfPessoa(p), getNome(p),getSobrenome(p), getSexo(p),getData(p));
    if(getMorador(p)){
        fprintf(txt, "Cep: %s Face: %s Numero: %d Complemento: %s\n", getCepMorador(p), getFace(p),getNum(p),getComplemento(p));
    }else{
        if(getSexo(p)=='M'){
            fprintf(txt,"Nao e morador\n");
        }else{
            fprintf(txt,"Nao e moradora\n");
        }
    }
    fprintf(txt,"\n");
}

void print_rip_txt(FILE* txt, Pessoa p){
    fprintf(txt, "Cpf: %s\nNome: %s %s Sexo: %c Dia de nasciento: %s\n", getCpfPessoa(p), getNome(p),getSobrenome(p), getSexo(p),getData(p));
    if(getMorador(p)){
        fprintf(txt, "Cep: %s Face: %s Numero: %d Complemento: %s\n", getCepMorador(p), getFace(p),getNum(p),getComplemento(p));
    }
    fprintf(txt,"Faleceu\n");
    fprintf(txt,"\n");
}

void print_dspj_txt(FILE* txt, Pessoa p){
    fprintf(txt, "Cpf: %s\nNome: %s %s Sexo: %c Dia de nasciento: %s\n", getCpfPessoa(p), getNome(p),getSobrenome(p), getSexo(p),getData(p));
    fprintf(txt, "O despejo ocorreu em:\n");
    fprintf(txt, "Cep: %s Face: %s Numero: %d Complemento: %s\n", getCepMorador(p), getFace(p),getNum(p),getComplemento(p));
    fprintf(txt,"\n");
}