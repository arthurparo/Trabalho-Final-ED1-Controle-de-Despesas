/* Bibliotecas necessaárias para o programa funcionar */
#include <stdio.h>
#include <stdlib.h>

/* Incluimos a pasta "gerenciador.h" pois o código precisa dela para rodar */
#include "gerenciador.h"

/* Implementação da função "inserir" */
void inserir(No **inicio_da_lista, Despesa despesa) {

    /* Pede ao sistema um pedaço de memória do tamanho do "nó" */
    No *novo_no = malloc(sizeof(No));

    /* Se o nó estiver vazio, a função "malloc" retorna NULL */
    if (novo_no == NULL) {
        printf("Erro: Falha ao alocar memória para um novo nó\n");
        return; 
    }

   /* O novo nó recebe os dados da despesa */
    novo_no->dado = despesa;

    /* O ponteiro aponta para o próximo nó, que antes era o nó inicial da lista */
    novo_no->proximo = *inicio_da_lista;

    /* O novo nó torna-se o nó do início da lista */
    *inicio_da_lista = novo_no;
}

/* Implementação da função "imprimir" */
void imprimir(No *inicio_da_lista) {
    
    No *no_atual = inicio_da_lista; /* Ponteiro que ajuda a seguir a lista */
    float total = 0.0f; /* Variável para somar as despesas */
    int contador = 1; /* Variável para numerar as despesas */

    printf("\n--- LISTA DE DESPESAS ---\n");
   
    /* Caso a lista esteja vazia, será retornado NULL */
    if (no_atual == NULL) {
        printf("Nenhuma despesa cadastrada.\n");
        return;
    }

    /* Loop para continuar o programa enquanto não chegar no final da lista */
    while (no_atual != NULL) {
        Despesa d = no_atual->dado; 
        printf("--------------------------\n");
        printf("Despesa #%d\n", contador); 
        printf("Nome da despesa: %s\n", d.descricao);
        printf("Valor: R$ %.2f\n", d.valor); 
        printf("Data: %02d/%02d/%d\n", d.dia, d.mes, d.ano); 
        total += d.valor;

        /* Utiliza-se essa função para avançar para o próximo nó */
        no_atual = no_atual->proximo;
        contador++; 
    }
    printf("==========================\n");
    printf("TOTAL DAS DESPESAS: R$ %.2f\n", total);
    printf("==========================\n");
}

/* Implementação da função "remover" */
int remover(No **inicio_da_lista, int posicao) {
    
    /* Caso não tenha nada para remover, ou for escolhido uma opção inexistente, o programa retorna zero (0) */
    if (*inicio_da_lista == NULL || posicao < 1) return 0; 

    /* Criação de um ponteiro temporário */
    No *pont_temp = *inicio_da_lista;

    /* Remoção do nó na posição 1 (primeiro nó) */
    if (posicao == 1) {
        *inicio_da_lista = pont_temp->proximo; /* Transforma o segundo nó no primeiro nó*/
        free(pont_temp); /* Libera a memória para o sistema */
        return 1; 
    }

    /* Remoção de um nó no meio da lista ou no final */
    for (int i = 1; pont_temp != NULL && i < posicao - 1; i++) {
        pont_temp = pont_temp->proximo;
    }

    /* Caso "pont", ou "pont->proximo", for NULL, sua posição era maior que o tamanho da lista */
    if (pont_temp == NULL || pont_temp->proximo == NULL) return 0; /* Retorna zero (0) */

    /* Nó que vamos remover*/
    No *no_remover = pont_temp->proximo;
    
    /* O ponteiro ignora o nó que apagamos e se liga ao próximo nó */
    pont_temp->proximo = no_remover->proximo;
    
    /* Liberar a memoria do nó */
    free(no_remover);

    return 1;
}

/* Implementação da função "salvar" */
void salvar(No *inicio_da_lista, const char *nome_arquivo) {
    
    /* Utilização de "escrita binária" (wb) */
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) return;

    /* Segue a lista e escreve o "dado" dos nós */
    for (No *atual = inicio_da_lista; atual != NULL; atual = atual->proximo) {
        fwrite(&atual->dado, sizeof(Despesa), 1, arquivo);
    }
    fclose(arquivo); /* Fecha o arquivo para assegurar que tudo foi salvo */
}

/* Implementação da função "carregar arquivo" */
No* carregar_arquivo(const char *nome_arquivo) {
    
    /* Utilização de "leitura binária" (rb) */
    FILE *arquivo = fopen(nome_arquivo, "rb");
   
    /* Caso o arquivo não exista, retorna NULL */
    if (!arquivo) return NULL;

    No *lista = NULL; /* Começa com a lista vazia */
    Despesa pont_temp; /* Variável temporária para armazenar os dados */

    /* Utiliza-se esse loop para ler uma "Despesa" de cada vez do arquivo */
    while (fread(&pont_temp, sizeof(Despesa), 1, arquivo)) {
        
        /* Cada "Despesa" lida é armazenada na lista em memória */
        inserir(&lista, pont_temp);
    }
    fclose(arquivo);
    return lista; /* Retorna o ponteiro para o início da lista que criamos */
}

/* Implementação da função "liberar memória" */
void liberar_memoria(No **inicio_da_lista) {
    No *atual = *inicio_da_lista;
    No *proximo; /* Ponteiro auxiliar */

    while (atual != NULL) {
        proximo = atual->proximo; /* Guarda o endereço do próximo nó */
        free(atual); /* Libera a memória do nó atual */
        atual = proximo; /* Segue para o próximo nó */
    }
    
    /* Indica que o ponteiro original na pasta "main" aponte para NULL (lista vazia) */
    *inicio_da_lista = NULL;
}