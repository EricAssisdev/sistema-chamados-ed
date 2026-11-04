#include <stdio.h>
#include <stdlib.h>
#include "lista_ord.h"

void lista_inicializar(ListaOrdenada *l) {
    l->inicio = NULL;
    l->total = 0;
}

int lista_vazia(const ListaOrdenada *l) {
    return l->inicio == NULL;
}

int lista_inserir(ListaOrdenada *l, Chamado c) {
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (!novo) return 0;

    novo->dado = c;
    novo->proximo = NULL;

    if (l->inicio == NULL || c.prioridade > l->inicio->dado.prioridade) {
        novo->proximo = l->inicio;
        l->inicio = novo;
    } else {
        NoLista *atual = l->inicio;
        while (atual->proximo != NULL && atual->proximo->dado.prioridade >= c.prioridade) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
    l->total++;
    return 1;
}

int lista_remover_inicio(ListaOrdenada *l, Chamado *c) {
    if (lista_vazia(l)) return 0;

    NoLista *temp = l->inicio;
    *c = temp->dado;
    l->inicio = temp->proximo;
    free(temp);
    l->total--;
    return 1;
}

void lista_imprimir(const ListaOrdenada *l) {
    if (lista_vazia(l)) {
        printf("Lista vazia.\n");
        return;
    }
    NoLista *atual = l->inicio;
    while (atual != NULL) {
        imprimir_chamado(&atual->dado);
        atual = atual->proximo;
    }
}

void lista_liberar(ListaOrdenada *l) {
    NoLista *atual = l->inicio;
    while (atual != NULL) {
        NoLista *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    l->inicio = NULL;
    l->total = 0;
}
