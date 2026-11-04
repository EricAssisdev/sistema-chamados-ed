#ifndef HEAP_MAX_H
#define HEAP_MAX_H

#include "chamado.h"

#define CAPACIDADE_HEAP 100

typedef struct {
    Chamado itens[CAPACIDADE_HEAP];
    int total;
} MaxHeap;

void heap_inicializar(MaxHeap *h);
int heap_inserir(MaxHeap *h, Chamado c);
int heap_extrair_max(MaxHeap *h, Chamado *c);
int heap_vazio(const MaxHeap *h);
void heap_imprimir(const MaxHeap *h);

#endif
