#ifndef FILA_FIFO_H
#define FILA_FIFO_H

#include "chamado.h"

#define CAPACIDADE_FILA 100

typedef struct {
    Chamado itens[CAPACIDADE_FILA];
    int inicio;
    int fim;
    int total;
} FilaFIFO;

void fila_inicializar(FilaFIFO *f);
int fila_enfileirar(FilaFIFO *f, Chamado c);
int fila_desenfileirar(FilaFIFO *f, Chamado *c);
int fila_vazia(const FilaFIFO *f);
void fila_imprimir(const FilaFIFO *f);

#endif
