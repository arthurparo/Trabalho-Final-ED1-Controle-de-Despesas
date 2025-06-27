/* Essa função permite que o computador só compile a definição de "Despesa" uma única vez,
permitindo que não haja erros na hora de compilar o código */
#ifndef despesas_h
#define despesas_h

/* A função "struct" agrupa diferentes tipos de variáveis em uma única estrutura. Utilizamos o
"typedef" para dar um nome à essa estrutura, que no caso escolhemos "Despesa". Essa função nos permite 
escrever apenas "Despesa" ao invés de "struct despesa", facilitando leitura do código */
typedef struct despesa {

    /* Um array de caracteres (de tamanho 100) usado para guardar a descrição da despesas */
    char descricao[100];

    /* Utilizamos "float" ao invés de "int" para representar dinheiro, pois ele suporta casas decimais */
    float valor;

    /* Utilizamos "int" para representar a data porque datas devem ser números inteiros, tanto o dia,
    quanto o mês e o ano */
    int dia, mes, ano;

/* É o nome escolhido da função "struct" por meio do "typedef" */
} Despesa;

/* Finaliza a primeira função do código */
#endif