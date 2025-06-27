#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "gerenciador.h" 
#include "historico.h"       


static bool data_valida(int dia, int mes, int ano) {
    if ( dia < 1 || dia > 31 ) { return false; }
    if ( mes < 1 || mes > 12 ) { return false; }
    if ( ano < 1925 || ano > 2125 ) { return false; } 
    return true;
}

/* Função para criar um "menu" com as opções do programa */
void menu() {

    system("cls || clear"); /* Função para limpar a tela a cada execução do código (evitar poluição visual) */
    printf("===================================\n");
    printf("    CONTROLE DE DESPESAS PESSOAIS\n");
    printf("===================================\n");
    printf("1. Adicionar nova despesa\n");
    printf("2. Listar todas as despesas\n");
    printf("3. Remover despesa\n");
    printf("4. Ver histórico de ações\n");
    printf("0. Salvar e Sair\n");
    printf("===================================\n");
    printf("Escolha uma opção: ");
}

/* Implementação da função "main", a função principal do programa */
int main() {


    /* Inicialização dos ponteiros iniciais das listas como NULL*/
    No *lista_de_despesas = NULL;
    NoHistorico *lista_de_historico = NULL;
    const char *nome_arquivo = "Controle de Despesas"; /* Nome do arquivo de dados */
    int opcao;

    /* Carrega os dados salvos da última seção */
    lista_de_despesas = carregar_arquivo(nome_arquivo);

    /* Registra a primeira ação no histórico */
    adicionar_acao(&lista_de_historico, "Sessão iniciada e despesas carregadas do arquivo.");

    /* Loop principal do programa */
    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        /* A função "switch" direciona o programa para o bloco de código correto, dependendo da escolha do usuário */
        switch (opcao) {
            case 1: { /* Caso 1: Adicionar uma nova despesa */
                Despesa nova_despesa;
                char buffer_historico[200]; 
                bool data_possivel;

                printf("Digite o nome da despesa: ");
                scanf(" %[^\n]", nova_despesa.descricao);
                
                printf("Digite o valor (ex.: 19.99): ");
                scanf("%f", &nova_despesa.valor); 

                do {
                    printf("Digite a data (dd mm aaaa): ");
                    scanf("%d %d %d", &nova_despesa.dia, &nova_despesa.mes, &nova_despesa.ano);
                    data_possivel = data_valida(nova_despesa.dia, nova_despesa.mes, nova_despesa.ano);
                    if (!data_possivel) {
                        printf("Data inválida. Insira novamente. \n");
                    }
                } while (!data_possivel);

                inserir(&lista_de_despesas, nova_despesa);
                
                /* A função "sprintf" formata a spring e salva em uma variável, ao invés de imprimir na tela */
                sprintf(buffer_historico, "Despesa '%s' (R$%.2f) criada.", nova_despesa.descricao, nova_despesa.valor);
                adicionar_acao(&lista_de_historico, buffer_historico);
                
                printf("\nDespesa adicionada com sucesso.\n");
                break; 
            }
            case 2: /* Caso 2: Listar todas as despesas */
                imprimir(lista_de_despesas);
                adicionar_acao(&lista_de_historico, "Lista de despesas exibida.");
                break;
            case 3: { /* Caso 3: Remover despesa */
                int pos_remover;
                char buffer_historico[200];

                /* Imprime todas as despesas para o usuário */
                imprimir(lista_de_despesas);
                printf("\nDigite o número (#) da despesa que deseja remover: ");
                scanf("%d", &pos_remover);
                
                /* Remove a despesa escolhida pelo usuário */
                if (remover(&lista_de_despesas, pos_remover)) {
                    sprintf(buffer_historico, "Despesa na posição #%d foi removida.", pos_remover);
                    adicionar_acao(&lista_de_historico, buffer_historico); /* Adiciona a ação de remover no histórico */
                    printf("\nDespesa removida com sucesso.\n");
                } else { /* Caso o usuário tente remover uma despesa que não existe */
                    adicionar_acao(&lista_de_historico, "Tentativa de remoção de despesa inválida.");
                    printf("\nFalha ao remover. Posição inválida ou lista vazia.\n");
                }
                break;
            }
            case 4: { /* Caso 4: Ver histórico de ações */
                imprimir_historico(lista_de_historico);
                break;
            }
            case 0: { /* Caso "0": Salvar e sair do programa */
                salvar(lista_de_despesas, nome_arquivo);
                adicionar_acao(&lista_de_historico, "Dados salvos e sessão encerrada.");
                break;
            }

            default: /* Caso seja escolhido uma opção que não existe */
                printf("\nOpção inválida! Tente novamente.\n");
        }

        /* Pausa para o usuário ler se a ação solicitada teve êxito ou erro */
        if (opcao != 0) {
            printf("\nPressione a tecla enter para voltar ao menu.");
            getchar(); 
        }

    } while (opcao != 0); /* Continua o loop enquanto a opção de sair não for escolhida */
    
    /* Libera a memória removida depois de usar o programa */
    liberar_memoria(&lista_de_despesas);
    liberar_historico(&lista_de_historico);
    printf("\nPrograma finalizado.\n");

    return 0;
}