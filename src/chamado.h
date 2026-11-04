#ifndef CHAMADO_H
#define CHAMADO_H

typedef struct {
    int id;
    char cliente[50];
    char descricao[100];
    int prioridade;
    int ordem;
} Chamado;

void imprimir_chamado(const Chamado *c);

#endif
