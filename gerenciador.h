#ifndef gerenciador_h
#define gerenciador_h

/* Incluímos a pasta "despesas.h" porque o código precisa dela para funcionar */
#include "despesas.h"


typedef struct Node {

    /* Cada "nó" (node) vai possui um dado do tipo "Despesa"  */
    Despesa dado;

    /* É um ponteiro que ponta para o próximo nó da sequência */
    struct Node *proximo;

} No;

/* Insere no início da lista uma despesa */
void inserir(No **inicio_da_lista, Despesa despesa);

/* Imprime as despesas que foram cadastradas no sistema */
void imprimir(No *inicio_da_lista);

/* Salva os ponteiros em um arquivo binário */
void salvar(No *inicio_da_lista, const char *nome_arquivo);

/* Carrega os dados de um arquivo e recria a lista */
No* carregar_arquivo(const char *nome_arquivo);

/* Libera a memória alocada em cada nó da lista */
void liberar_memoria(No **inicio_da_lista);

/* Remove um nó da lista (consequentemente uma despesa previamente cadastrada no sistema) */
int remover(No **inicio_da_lista, int posicao);

#endif