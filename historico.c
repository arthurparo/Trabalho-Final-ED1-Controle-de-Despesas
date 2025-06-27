#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

/* Implementação da função "adicionar ação", adiciona uma mensagem de ação no início da lista de histórico */
void adicionar_acao(NoHistorico **inicio_historico, const char *mensagem) {
    NoHistorico *acao = malloc(sizeof(NoHistorico));
    if (acao == NULL) return;

    /* A função "strncpy" evita sobrecarga de buffer, pois copia um número específico de caracteres de uma string de origem para uma string de destino */
    strncpy(acao->mensagem, mensagem, 199);
    acao->mensagem[199] = '\0'; 

    acao->proximo = *inicio_historico;
    *inicio_historico = acao;
}

/* Implementação da função "imprimir histórico", imprime todas as ações registradas no histórico */
void imprimir_historico(NoHistorico *inicio_historico) {
    printf("\n--- HISTÓRICO DE AÇÕES ---\n");
    if (inicio_historico == NULL) { /* Caso não tenha tido nenhuma ação registrada, retorna NULL */
        printf("Nenhuma ação registrada.\n");
        return;
    }
    for (NoHistorico *atual = inicio_historico; atual != NULL; atual = atual->proximo) {
        printf("- %s\n", atual->mensagem);
    }
    printf("--------------------------\n");
}

/* Implementação da função de "liberar histórico", segue a mesma lógica da função de liberação de memória da lista,
mas, dessa vez, libera a memória do histórico */
void liberar_historico(NoHistorico **inicio_historico) {
    NoHistorico *atual = *inicio_historico;
    while (atual != NULL) {
        NoHistorico *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *inicio_historico = NULL;
}
