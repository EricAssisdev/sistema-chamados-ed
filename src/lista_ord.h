#ifndef LISTA_ORD_H
#define LISTA_ORD_H

#include "chamado.h"

typedef struct NoLista {
    Chamado dado;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
    int total;
} ListaOrdenada;

void lista_inicializar(ListaOrdenada *l);
int lista_inserir(ListaOrdenada *l, Chamado c);
int lista_remover_inicio(ListaOrdenada *l, Chamado *c);
int lista_vazia(const ListaOrdenada *l);
void lista_imprimir(const ListaOrdenada *l);
void lista_liberar(ListaOrdenada *l);

#endif
