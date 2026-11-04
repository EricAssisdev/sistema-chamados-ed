# Roteiro de Apresentação do Trabalho

Estruturas de Dados Aplicadas a Situações Reais  
UniRuy Wyden - Prof. MSc Eng Heleno Cardoso

---

## 1. Situação-Problema Real
- **Cenário:** Central de Helpdesk / Suporte de TI de uma empresa.
- **Dilema:** Chamados chegam a todo momento com diferentes níveis de gravidade (1-Baixa, 2-Média, 3-Alta).
- **Necessidade:** Garantir que incidentes graves (ex.: servidor indisponível) sejam tratados com prioridade máxima, sem ignorar a ordem cronológica para chamados de mesma prioridade.

---

## 2. Solução Proposta
- Implementação em linguagem C de um sistema de despacho de chamados.
- Três estruturas de dados foram construídas para gerenciar a mesma fila de chamados, permitindo comparar comportamento, tempos de resposta e lógica de atendimento.

---

## 3. Estrutura de Dados 1: Fila Sequencial Circular (FIFO)
- **Aplicação:** Atendimento estritamente por ordem de chegada.
- **Complexidade:** Inserção em $O(1)$ e Atendimento em $O(1)$.
- **Vantagem:** Muito simples de implementar e de baixo custo operacional.
- **Limitação:** Ignora totalmente a prioridade do chamado.

---

## 4. Estrutura de Dados 2: Lista Encadeada Ordenada
- **Aplicação:** Nós encadeados inseridos de maneira a manter a lista sempre ordenada da maior para a menor prioridade.
- **Complexidade:** Inserção em $O(n)$ e Atendimento em $O(1)$.
- **Vantagem:** O chamado mais urgente está sempre na cabeça da lista.
- **Limitação:** Custo de inserção cresce linearmente com a quantidade de chamados acumulados.

---

## 5. Estrutura de Dados 3: Fila de Prioridade com Max-Heap
- **Aplicação:** Árvore binária de prioridade organizada em array contíguo.
- **Complexidade:** Inserção em $O(\log n)$ e Atendimento em $O(\log n)$.
- **Vantagem:** Custo balanceado e escalável mesmo com alto fluxo de chamados.
- **Limitação:** Lógica de subida e descida no heap requer maior cuidado na implementação.

---

## 6. Comparação entre as Três EDs
- **FIFO:** Rápida, mas inadequada para a regra de negócio da vida real.
- **Lista Ordenada:** Adequada funcionalmente, mas não escalável na inserção para grandes volumes.
- **Max-Heap:** Melhor custo-benefício computacional para sistemas com chegadas e atendimentos contínuos.

---

## 7. Escolha da Melhor ED e Justificativa
- **Escolhida:** **Max-Heap (Fila de Prioridade)**.
- **Por quê?** Porque um sistema de helpdesk real recebe e resolve chamados a todo instante. O Max-Heap garante que tanto a chegada de um novo chamado quanto o despacho do chamado prioritário ocorram em tempo logarítmico $O(\log n)$, respeitando o SLA de urgência de forma eficiente e escalável.

---

## 8. Demonstração Prática
1. Execução do programa compilado (`sistema_chamados.exe`).
2. Opção 6 (Comparação de lote): demonstração de 5 chamados idênticos passando pelas três estruturas.
3. Observação em tela:
   - A Fila FIFO atende o mouse com defeito antes do servidor fora do ar.
   - A Lista e o Heap atendem primeiro os dois chamados críticos (servidor e firewall).
