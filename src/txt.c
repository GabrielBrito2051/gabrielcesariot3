#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/txt.h"
#include "../include/quadra.h"
#include "../include/pessoa.h"

void print_rq_txt(FILE* txt, Pessoa p){
    fprintf(txt,"Morador:%s %s\tCpf:%s virou sem-teto\n", getNome(p), getSobrenome(p), getCpfPessoa(p));
}

void print_censo_txt(FILE* txt, int th, int tm, double mh, int nh, int nm, double ph, double pm, int ts, double phs, double pms){
    
}

void print_h_txt(FILE* txt, Pessoa p){
    fprintf(txt, "Cpf: %s\nNome: %s %s Sexo: %c Dia de nasciento: %s\n", getCpfPessoa(p), getNome(p),getSobrenome(p), getSexo(p),getData(p));
    if(getMorador(p)){
        fprintf(txt, "Cep: %s Face: %c Numero: %d Complemento: %s\n", getCepMorador(p), getFace(p),getNum(p),getComplemento(p));
    }
}

void print_rip_txt(FILE* txt, Pessoa p){
    fprintf(txt, "Cpf: %s\nNome: %s %s Sexo: %c Dia de nasciento: %s\n", getCpfPessoa(p), getNome(p),getSobrenome(p), getSexo(p),getData(p));
    if(getMorador(p)){
        fprintf(txt, "Cep: %s Face: %c Numero: %d Complemento: %s\n", getCepMorador(p), getFace(p),getNum(p),getComplemento(p));
    }
}

void print_dspj_txt(FILE* txt, Pessoa p){
    fprintf(txt, "Cpf: %s\nNome: %s %s Sexo: %c Dia de nasciento: %s\n", getCpfPessoa(p), getNome(p),getSobrenome(p), getSexo(p),getData(p));
    fprintf(txt, "O despejo ocorreu em: ");
    fprintf(txt, "Cep: %s Face: %c Numero: %d Complemento: %s\n", getCepMorador(p), getFace(p),getNum(p),getComplemento(p));
}