#ifndef FUNCOES_H
#define FUNCOES_H

#include "raylib.h"
#include "cartas.h"
#include <stdio.h>
#include <stdbool.h>

// Structures
typedef struct {
    Texture2D azul;
    Texture2D verde;
    Texture2D amarelo;
    Texture2D vermelho;
    Texture2D azulST;
    Texture2D verdeST;
    Texture2D amareloST;
    Texture2D vermelhoST;
} Molduras;

typedef struct {
    Texture2D seta;
    Texture2D TexturaFundo;
    Texture2D editar;
    Texture2D tCan;
    Texture2D add;
    Texture2D atencao;
} Textura;

typedef struct {
    Font tituloCartas;
    Font tituloTelas;
    Font atributoCartas;
} Fonte;


// Function Prototypes
int contarcartas(FILE *arq);
cartas configuracoesIniciais(FILE *arq); //Should this be a 'cartas *'?
cartas *carregarDeck(const char *nomeArquivo, int *quantidadeCartas);

// Resource loading and unloading
Fonte loadFonte();
void unloadFonte(Fonte fonte);
Molduras loadMolduras();
void unloadMolduras(Molduras molduras);
Textura loadTexturas();
void unloadTexturas(Textura texturas);
void loadIMGCartas(cartas *cartas, int quantidadeCartas); 

int obterAtributo(cartas c, int atributo);


#endif