# Sistema de Gerenciamento de Chamados com Estruturas de Dados

Trabalho prático da disciplina de Estruturas de Dados (UniRuy Wyden)  
Docente: Prof. MSc Eng Heleno Cardoso

---

## 1. Situação-Problema Real

Em um setor de suporte técnico de TI (Helpdesk), diversas solicitações de atendimento chegam simultaneamente por funcionários ou clientes. Cada solicitação possui um nível de gravidade ou urgência:
- **Alta (3):** Ex.: Servidor principal indisponível, incidente de segurança.
- **Média (2):** Ex.: Falha em software departamental, lentidão em relatórios.
- **Baixa (1):** Ex.: Solicitação de troca de periféricos (mouse, teclado).

Atender chamados estritamente por ordem de chegada pode acarretar paradas críticas na operação da empresa enquanto problemas triviais são resolvidos. Por isso, a escolha correta da estrutura de dados para o escalonamento dos chamados é determinante para o cumprimento de acordos de nível de serviço (SLA).

---

## 2. Solução Computacional

O sistema foi desenvolvido em linguagem C e implementa três estruturas de dados alternativas para gerenciar os chamados:
1. **Fila Sequencial Circular (FIFO)**
2. **Lista Encadeada Ordenada por Prioridade**
3. **Fila de Prioridade baseada em Heap Binário de Máximo (Max-Heap)**

O programa permite inserir chamados simultaneamente nas três estruturas e comparar na prática a ordem e a lógica de atendimento de cada uma.

---

## 3. Análise das 3 Estruturas de Dados

### Estrutura 1: Fila Sequencial Circular (FIFO)
- **Como é utilizada:** Os chamados entram no final da fila (`enfileirar`) e são atendidos a partir do início (`desenfileirar`).
- **Operações:** `fila_enfileirar`, `fila_desenfileirar`, `fila_vazia`.
- **Vantagens:** Implementação simples, operações de inserção e remoção em tempo constante $O(1)$.
- **Limitações:** Não considera a gravidade do chamado; um problema crítico pode esperar indefinidamente atrás de chamados triviais.
- **Impacto no problema:** Inadequado para ambientes com SLAs críticos.

### Estrutura 2: Lista Encadeada Ordenada
- **Como é utilizada:** Cada novo chamado é alocado dinamicamente e inserido na posição correspondente à sua prioridade (maior prioridade mais próxima do início).
- **Operações:** `lista_inserir` (ordenada), `lista_remover_inicio`, `lista_liberar`.
- **Vantagens:** O chamado de maior prioridade sempre está imediatamente disponível no início ($O(1)$ para remoção); alocação dinâmica de nós.
- **Limitações:** A inserção exige percorrer a lista para encontrar a posição correta, com custo $O(n)$ no pior caso.
- **Impacto no problema:** Eficiente para pequenos volumes de chamados, mas perde desempenho conforme o número de chamados acumulados aumenta.

### Estrutura 3: Max-Heap (Fila de Prioridade)
- **Como é utilizada:** Os chamados são mantidos em uma árvore binária quase completa implementada sobre vetor, onde o elemento de maior prioridade sempre ocupa a raiz (índice 0).
- **Operações:** `heap_inserir` (com subida/heapify-up), `heap_extrair_max` (com descida/heapify-down).
- **Vantagens:** Equilíbrio de desempenho: inserção em $O(\log n)$ e remoção do chamado prioritário em $O(\log n)$.
- **Limitações:** Implementação mais elaborada que a fila e a lista simples.
- **Impacto no problema:** Escalável e robusta para grandes volumes de chamados com múltiplos níveis de criticidade.

---

## 4. Comparação Técnica

| Critério | Fila FIFO | Lista Encadeada Ordenada | Max-Heap (Priority Queue) |
| :--- | :---: | :---: | :---: |
| **Facilidade de Implementação** | Alta (muito simples) | Média | Moderada |
| **Custo de Inserção** | $O(1)$ | $O(n)$ | $O(\log n)$ |
| **Custo de Remoção (Atendimento)**| $O(1)$ | $O(1)$ | $O(\log n)$ |
| **Acesso ao Mais Urgente** | $O(n)$ (requer varredura) | $O(1)$ (está na cabeça) | $O(1)$ (está na raiz) |
| **Uso de Memória** | Vetor estático circular | Dinâmico (ponteiros por nó) | Vetor contíguo |
| **Adequação ao Problema Real** | Baixa | Média | **Alta (Ideal)** |

---

## 5. Justificativa da Escolha da Melhor Estrutura

A estrutura mais adequada para a situação-problema é o **Max-Heap (Fila de Prioridade)**.

**Justificativa Técnica:**
1. Em um sistema de suporte real, as duas operações fundamentais ocorrem em frequência equilibrada: chegada de novos chamados e atendimento de chamados prioritários.
2. A **Fila FIFO**, embora execute ambas as operações em $O(1)$, falha no requisito de negócio de atender chamados urgentes antes dos triviais.
3. A **Lista Encadeada Ordenada** resolve a questão da prioridade, mas transfere o custo para a inserção ($O(n)$), o que penaliza o sistema sob alta carga de chamados.
4. O **Max-Heap** oferece um custo balanceado de $O(\log n)$ tanto para inserção quanto para atendimento, garantindo que mesmo com milhares de chamados pendentes, o tempo de resposta permaneça praticamente instantâneo e rigorosamente alinhado aos SLAs de urgência.

---

## 6. Como Compilar e Executar

### Pré-requisitos
- Compilador C (`gcc` / MinGW ou Clang)

### No Windows (prompt de comando ou terminal):
```cmd
build.bat
sistema_chamados.exe
```

Ou diretamente via `gcc`:
```cmd
gcc -Wall -Wextra -std=c99 src/fila_fifo.c src/lista_ord.c src/heap_max.c src/main.c -o sistema_chamados.exe
.\sistema_chamados.exe
```

### No Linux / macOS:
```bash
make
./sistema_chamados
```
