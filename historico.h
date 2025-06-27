#ifndef historico_h
#define historico_h

/* Função do nó da lista do histórico */
typedef struct Historico {
    char mensagem[200];
    struct Historico *proximo;
} NoHistorico;

/* As funções que manipulam o histórico de ações */
void adicionar_acao(NoHistorico **inicio_historico, const char *mensagem);
void imprimir_historico(NoHistorico *inicio_historico);
void liberar_historico(NoHistorico **inicio_historico);

#endif
