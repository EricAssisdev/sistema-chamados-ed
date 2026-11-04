#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/*
 * Trabalho de Estrutura de Dados - Cenario Real
 * Tema: Fila de Atendimento com Prioridade (Protocolo de Manchester)
 *
 * Cores do Protocolo de Manchester:
 * 1 - Vermelho (Emergencia - atendimento imediato)
 * 2 - Laranja  (Muito Urgente)
 * 3 - Amarelo  (Urgente)
 * 4 - Verde    (Pouco Urgente)
 * 5 - Azul     (Nao Urgente)
 */

typedef struct {
    int id;
    char nome[50];
    int prioridade;
    int ordem_chegada;
} Paciente;

// Funcao auxiliar para saber se o paciente A tem mais prioridade que o paciente B
int tem_maior_prioridade(Paciente a, Paciente b) {
    if (a.prioridade < b.prioridade) {
        return 1; // Menor numero = maior gravidade (1 e mais grave que 5)
    }
    if (a.prioridade > b.prioridade) {
        return 0;
    }
    // Em caso de empate na prioridade, atende quem chegou primeiro (FIFO)
    return (a.ordem_chegada < b.ordem_chegada);
}

const char* nome_prioridade(int p) {
    switch (p) {
        case 1: return "Vermelho (Emergencia)";
        case 2: return "Laranja (Muito Urgente)";
        case 3: return "Amarelo (Urgente)";
        case 4: return "Verde (Pouco Urgente)";
        case 5: return "Azul (Nao Urgente)";
        default: return "Desconhecido";
    }
}

void imprimir_paciente(Paciente p) {
    printf("[ID %d | Chegada #%d] %s - %s\n", p.id, p.ordem_chegada, p.nome, nome_prioridade(p.prioridade));
}

/* =========================================================================
   ESTRUTURA DE DADOS 1: Vetor / Lista Nao-Ordenada
   - Inserir: O(1) (basta adicionar no final)
   - Atender: O(n) (procura o mais grave na lista toda e desloca os elementos)
   ========================================================================= */

Paciente fila_vetor[MAX];
int tam_vetor = 0;

void ed1_inserir(Paciente p) {
    if (tam_vetor < MAX) {
        fila_vetor[tam_vetor] = p;
        tam_vetor++;
    } else {
        printf("Fila cheia!\n");
    }
}

int ed1_atender(Paciente *atendido) {
    if (tam_vetor == 0) return 0;

    // Busca linear pelo paciente mais urgente
    int melhor = 0;
    for (int i = 1; i < tam_vetor; i++) {
        if (tem_maior_prioridade(fila_vetor[i], fila_vetor[melhor])) {
            melhor = i;
        }
    }

    *atendido = fila_vetor[melhor];

    // Desloca os outros pacientes para preencher o espaco
    for (int i = melhor; i < tam_vetor - 1; i++) {
        fila_vetor[i] = fila_vetor[i + 1];
    }
    tam_vetor--;
    return 1;
}

void ed1_listar(void) {
    printf("\n--- ED 1: Vetor Nao-Ordenado (%d pacientes) ---\n", tam_vetor);
    if (tam_vetor == 0) {
        printf("Fila vazia.\n");
        return;
    }
    for (int i = 0; i < tam_vetor; i++) {
        printf("Posicao %d: ", i + 1);
        imprimir_paciente(fila_vetor[i]);
    }
}

/* =========================================================================
   ESTRUTURA DE DADOS 2: Lista Simplesmente Encadeada Ordenada
   - Inserir: O(n) (percorre os nos ate achar a posicao de prioridade)
   - Atender: O(1) (remove direto o primeiro no da lista)
   ========================================================================= */

typedef struct No {
    Paciente dado;
    struct No *prox;
} No;

No *lista_encadeada = NULL;

void ed2_inserir(Paciente p) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = p;
    novo->prox = NULL;

    // Se a lista estiver vazia ou se o novo paciente for mais urgente que o primeiro
    if (lista_encadeada == NULL || tem_maior_prioridade(p, lista_encadeada->dado)) {
        novo->prox = lista_encadeada;
        lista_encadeada = novo;
    } else {
        // Percorre ate achar a posicao correta
        No *atual = lista_encadeada;
        while (atual->prox != NULL && !tem_maior_prioridade(p, atual->prox->dado)) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

int ed2_atender(Paciente *atendido) {
    if (lista_encadeada == NULL) return 0;

    No *temp = lista_encadeada;
    *atendido = temp->dado;
    lista_encadeada = lista_encadeada->prox;
    free(temp);
    return 1;
}

void ed2_listar(void) {
    printf("\n--- ED 2: Lista Encadeada Ordenada ---\n");
    if (lista_encadeada == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    No *atual = lista_encadeada;
    int pos = 1;
    while (atual != NULL) {
        printf("Posicao %d: ", pos++);
        imprimir_paciente(atual->dado);
        atual = atual->prox;
    }
}

/* =========================================================================
   ESTRUTURA DE DADOS 3: Fila de Prioridade com Heap Binario (Min-Heap)
   - Inserir: O(log n) (adiciona na folha e sobe organizando)
   - Atender: O(log n) (pega a raiz, coloca a ultima folha no topo e desce organizando)
   ========================================================================= */

Paciente heap[MAX];
int tam_heap = 0;

void trocar(Paciente *a, Paciente *b) {
    Paciente temp = *a;
    *a = *b;
    *b = temp;
}

void ed3_inserir(Paciente p) {
    if (tam_heap >= MAX) {
        printf("Heap cheio!\n");
        return;
    }

    // Coloca na ultima posicao e sobe
    heap[tam_heap] = p;
    int i = tam_heap;
    tam_heap++;

    while (i > 0) {
        int pai = (i - 1) / 2;
        if (tem_maior_prioridade(heap[i], heap[pai])) {
            trocar(&heap[i], &heap[pai]);
            i = pai;
        } else {
            break;
        }
    }
}

int ed3_atender(Paciente *atendido) {
    if (tam_heap == 0) return 0;

    *atendido = heap[0]; // O mais urgente esta sempre na raiz
    tam_heap--;

    if (tam_heap > 0) {
        heap[0] = heap[tam_heap]; // Coloca o ultimo na raiz e desce
        int i = 0;
        while (1) {
            int esq = 2 * i + 1;
            int dir = 2 * i + 2;
            int maior = i;

            if (esq < tam_heap && tem_maior_prioridade(heap[esq], heap[maior])) {
                maior = esq;
            }
            if (dir < tam_heap && tem_maior_prioridade(heap[dir], heap[maior])) {
                maior = dir;
            }

            if (maior != i) {
                trocar(&heap[i], &heap[maior]);
                i = maior;
            } else {
                break;
            }
        }
    }
    return 1;
}

void ed3_listar(void) {
    printf("\n--- ED 3: Heap Binario de Prioridade (%d pacientes) ---\n", tam_heap);
    if (tam_heap == 0) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Proximo no topo do Heap: ");
    imprimir_paciente(heap[0]);
    printf("Elementos armazenados no vetor do Heap:\n");
    for (int i = 0; i < tam_heap; i++) {
        printf("Indice %d: ", i);
        imprimir_paciente(heap[i]);
    }
}

/* =========================================================================
   PROGRAMA PRINCIPAL (MENU INTERATIVO)
   ========================================================================= */

int main(void) {
    int contador_chegada = 0;
    int proximo_id = 1;
    int opcao = -1;

    while (opcao != 0) {
        printf("\n=========================================\n");
        printf("  SISTEMA DE FILA DE TRIAGEM HOSPITALAR  \n");
        printf("=========================================\n");
        printf("1. Cadastrar paciente\n");
        printf("2. Chamar proximo paciente\n");
        printf("3. Visualizar as 3 Estruturas de Dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            break;
        }

        switch (opcao) {
            case 1: {
                Paciente p;
                p.id = proximo_id++;
                p.ordem_chegada = ++contador_chegada;

                printf("\nNome do paciente: ");
                scanf(" %49[^\n]", p.nome);

                printf("Prioridade de Manchester:\n");
                printf(" 1 - Vermelho (Emergencia)\n");
                printf(" 2 - Laranja (Muito Urgente)\n");
                printf(" 3 - Amarelo (Urgente)\n");
                printf(" 4 - Verde (Pouco Urgente)\n");
                printf(" 5 - Azul (Nao Urgente)\n");
                printf("Informe a prioridade (1 a 5): ");
                scanf("%d", &p.prioridade);

                if (p.prioridade < 1 || p.prioridade > 5) {
                    p.prioridade = 4; // Padrao verde se digitar errado
                }

                // Insere simultaneamente nas 3 estruturas para demonstrar
                ed1_inserir(p);
                ed2_inserir(p);
                ed3_inserir(p);

                printf("Paciente cadastrado com sucesso!\n");
                break;
            }

            case 2: {
                Paciente p1, p2, p3;
                if (!ed1_atender(&p1)) {
                    printf("\nNenhum paciente aguardando na fila!\n");
                } else {
                    ed2_atender(&p2);
                    ed3_atender(&p3);
                    printf("\n=========================================\n");
                    printf("        CHAMANDO PROXIMO PACIENTE         \n");
                    printf("=========================================\n");
                    printf("ED 1 (Vetor Nao-Ordenado) : ");
                    imprimir_paciente(p1);
                    printf("ED 2 (Lista Encadeada)    : ");
                    imprimir_paciente(p2);
                    printf("ED 3 (Heap de Prioridade) : ");
                    imprimir_paciente(p3);
                }
                break;
            }

            case 3:
                ed1_listar();
                ed2_listar();
                ed3_listar();
                break;

            case 0:
                printf("\nEncerrando o programa.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    }

    return 0;
}
