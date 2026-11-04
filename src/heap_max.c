#include <stdio.h>
#include "heap_max.h"

void heap_inicializar(MaxHeap *h) {
    h->total = 0;
}

int heap_vazio(const MaxHeap *h) {
    return h->total == 0;
}

static int maior_prioridade(Chamado a, Chamado b) {
    if (a.prioridade > b.prioridade) return 1;
    if (a.prioridade < b.prioridade) return 0;
    return a.ordem < b.ordem;
}

static void trocar(Chamado *a, Chamado *b) {
    Chamado temp = *a;
    *a = *b;
    *b = temp;
}

int heap_inserir(MaxHeap *h, Chamado c) {
    if (h->total == CAPACIDADE_HEAP) return 0;

    int i = h->total;
    h->itens[i] = c;
    h->total++;

    while (i > 0) {
        int pai = (i - 1) / 2;
        if (maior_prioridade(h->itens[i], h->itens[pai])) {
            trocar(&h->itens[i], &h->itens[pai]);
            i = pai;
        } else {
            break;
        }
    }
    return 1;
}

int heap_extrair_max(MaxHeap *h, Chamado *c) {
    if (heap_vazio(h)) return 0;

    *c = h->itens[0];
    h->total--;
    h->itens[0] = h->itens[h->total];

    int i = 0;
    while (1) {
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int maior = i;

        if (esq < h->total && maior_prioridade(h->itens[esq], h->itens[maior])) {
            maior = esq;
        }
        if (dir < h->total && maior_prioridade(h->itens[dir], h->itens[maior])) {
            maior = dir;
        }

        if (maior != i) {
            trocar(&h->itens[i], &h->itens[maior]);
            i = maior;
        } else {
            break;
        }
    }
    return 1;
}

void heap_imprimir(const MaxHeap *h) {
    if (heap_vazio(h)) {
        printf("Heap vazio.\n");
        return;
    }
    for (int i = 0; i < h->total; i++) {
        imprimir_chamado(&h->itens[i]);
    }
}
