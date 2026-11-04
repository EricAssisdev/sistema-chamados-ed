#include <stdio.h>
#include <string.h>
#include "chamado.h"
#include "fila_fifo.h"
#include "lista_ord.h"
#include "heap_max.h"

void imprimir_chamado(const Chamado *c) {
    const char *prio_str = "Baixa";
    if (c->prioridade == 2) prio_str = "Media";
    if (c->prioridade == 3) prio_str = "Alta";

    printf("[%s] ID: %d | Chegada: #%d | Cliente: %-10s | %s\n",
           prio_str, c->id, c->ordem, c->cliente, c->descricao);
}

static void simular_comparacao() {
    Chamado lista_teste[5] = {
        {101, "Carlos", "Mouse com defeito", 1, 1},
        {102, "Mariana", "Monitor sem imagem", 2, 2},
        {103, "Roberto", "Servidor principal fora do ar", 3, 3},
        {104, "Fernanda", "Solicitacao de acesso ao ERP", 1, 4},
        {105, "Lucas", "Falha de seguranca no firewall", 3, 5}
    };

    printf("\n=== LOTE DE CHAMADOS RECEBIDOS ===\n");
    for (int i = 0; i < 5; i++) {
        imprimir_chamado(&lista_teste[i]);
    }

    FilaFIFO fifo;
    fila_inicializar(&fifo);
    for (int i = 0; i < 5; i++) {
        fila_enfileirar(&fifo, lista_teste[i]);
    }

    printf("\n--- ORDEM DE ATENDIMENTO: 1. FILA FIFO ---\n");
    Chamado c;
    while (fila_desenfileirar(&fifo, &c)) {
        imprimir_chamado(&c);
    }

    ListaOrdenada lista;
    lista_inicializar(&lista);
    for (int i = 0; i < 5; i++) {
        lista_inserir(&lista, lista_teste[i]);
    }

    printf("\n--- ORDEM DE ATENDIMENTO: 2. LISTA ORDENADA ---\n");
    while (lista_remover_inicio(&lista, &c)) {
        imprimir_chamado(&c);
    }
    lista_liberar(&lista);

    MaxHeap heap;
    heap_inicializar(&heap);
    for (int i = 0; i < 5; i++) {
        heap_inserir(&heap, lista_teste[i]);
    }

    printf("\n--- ORDEM DE ATENDIMENTO: 3. MAX-HEAP (FILA DE PRIORIDADE) ---\n");
    while (heap_extrair_max(&heap, &c)) {
        imprimir_chamado(&c);
    }
}

int main() {
    int opcao;
    int contador_id = 1;
    int ordem_global = 1;

    FilaFIFO fifo;
    ListaOrdenada lista;
    MaxHeap heap;

    fila_inicializar(&fifo);
    lista_inicializar(&lista);
    heap_inicializar(&heap);

    do {
        printf("\n=========================================\n");
        printf("    SISTEMA DE CHAMADOS - ESTRUTURAS     \n");
        printf("=========================================\n");
        printf("1. Inserir chamado em todas as estruturas\n");
        printf("2. Atender proximo na Fila FIFO\n");
        printf("3. Atender proximo na Lista Ordenada\n");
        printf("4. Atender proximo no Max-Heap\n");
        printf("5. Visualizar estado das 3 estruturas\n");
        printf("6. Executar comparacao automatica de lote\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            break;
        }

        if (opcao == 1) {
            Chamado novo;
            novo.id = contador_id++;
            novo.ordem = ordem_global++;

            printf("Nome do cliente: ");
            scanf("%49s", novo.cliente);
            printf("Descricao do chamado: ");
            scanf(" %[^\n]", novo.descricao);
            printf("Prioridade (1 - Baixa, 2 - Media, 3 - Alta): ");
            scanf("%d", &novo.prioridade);

            if (novo.prioridade < 1) novo.prioridade = 1;
            if (novo.prioridade > 3) novo.prioridade = 3;

            fila_enfileirar(&fifo, novo);
            lista_inserir(&lista, novo);
            heap_inserir(&heap, novo);

            printf("Chamado #%d inserido com sucesso nas 3 estruturas.\n", novo.id);
        } else if (opcao == 2) {
            Chamado atendido;
            if (fila_desenfileirar(&fifo, &atendido)) {
                printf("\n[FIFO] Atendendo chamado:\n");
                imprimir_chamado(&atendido);
            } else {
                printf("\nFila FIFO vazia.\n");
            }
        } else if (opcao == 3) {
            Chamado atendido;
            if (lista_remover_inicio(&lista, &atendido)) {
                printf("\n[Lista Ordenada] Atendendo chamado:\n");
                imprimir_chamado(&atendido);
            } else {
                printf("\nLista Ordenada vazia.\n");
            }
        } else if (opcao == 4) {
            Chamado atendido;
            if (heap_extrair_max(&heap, &atendido)) {
                printf("\n[Max-Heap] Atendendo chamado:\n");
                imprimir_chamado(&atendido);
            } else {
                printf("\nMax-Heap vazio.\n");
            }
        } else if (opcao == 5) {
            printf("\n--- ESTADO ATUAL: FILA FIFO ---\n");
            fila_imprimir(&fifo);
            printf("\n--- ESTADO ATUAL: LISTA ORDENADA ---\n");
            lista_imprimir(&lista);
            printf("\n--- ESTADO ATUAL: MAX-HEAP ---\n");
            heap_imprimir(&heap);
        } else if (opcao == 6) {
            simular_comparacao();
        }

    } while (opcao != 0);

    lista_liberar(&lista);
    return 0;
}
