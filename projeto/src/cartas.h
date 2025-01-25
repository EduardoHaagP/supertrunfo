#ifndef CARTAS_H
#define CARTAS_H

typedef struct {
    char nome[51];
    char letra;
    int supertrunfo;
    int anoConstrucao;
    int altura;
    int visitasAnuais;
    int importanciaHistorica;
    int popularidade;
} cartas;

// Declarações das funções
void inserirCartas(cartas **deck, int *quantidadeCartas);
void listarCartas(cartas **deck, int *quantidadeCartas);
void pesquisarCartas(cartas **deck, int *quantidadeCartas);
void alterarCartas(cartas **deck, int *quantidadeCartas);
void excluirCartas(cartas **deck, int *quantidadeCartas);

#endif // CARTAS_H