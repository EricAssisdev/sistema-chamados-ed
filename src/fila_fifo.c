#include <stdio.h>
#include "fila_fifo.h"

void fila_inicializar(FilaFIFO *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int fila_vazia(const FilaFIFO *f) {
    return f->total == 0;
}

int fila_enfileirar(FilaFIFO *f, Chamado c) {
    if (f->total == CAPACIDADE_FILA) {
        return 0;
    }
    f->itens[f->fim] = c;
    f->fim = (f->fim + 1) % CAPACIDADE_FILA;
    f->total++;
    return 1;
}

int fila_desenfileirar(FilaFIFO *f, Chamado *c) {
    if (fila_vazia(f)) {
        return 0;
    }
    *c = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % CAPACIDADE_FILA;
    f->total--;
    return 1;
}

void fila_imprimir(const FilaFIFO *f) {
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        imprimir_chamado(&f->itens[idx]);
        idx = (idx + 1) % CAPACIDADE_FILA;
    }
}
