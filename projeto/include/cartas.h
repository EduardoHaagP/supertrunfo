#ifndef CARTAS_H
#define CARTAS_H

#include "raylib.h"

typedef struct {
    char nome[51];
    char letra;
    int supertrunfo;
    int anoConstrucao;
    int altura;
    int visitasAnuais;
    int importanciaHistorica;
    int popularidade;
    Texture2D img;
    char arqimg[100];
} cartas;

// Declarações das funções
void salvarNoCSV(cartas **deck, int *quantidadeCartas);
void inserirCartas(cartas **deck, int *quantidadeCartas);
void excluirCartas(cartas **deck, int *quantidadeCartas);
void alterarCartas(cartas **deck, int *quantidadeCartas);


#endif // CARTAS_H