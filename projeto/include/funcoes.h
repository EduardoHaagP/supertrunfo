#ifndef FUNCOES_H
#define FUNCOES_H

#include "raylib.h"
#include "cartas.h"
#include <stdio.h>


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
    Texture2D setaON;
    Texture2D setaOFF;
    Texture2D TexturaFundo;
} Textura;

typedef struct {
    Font tituloCartas; //projeto/assets/font/Avenir-Black.ttf
    Font tituloTelas; //projeto/assets/font/Avenir-Book.ttf
    Font letraCarta; //projeto/assets/font/Avenir-Heavy.ttf
    Font atributoCartas; //projeto/assets/font/AvenirNextCyr-Medium.ttf
} Fonte;


int contarcartas(FILE *arq);
cartas configuracoesIniciais(FILE *arq);
cartas *carregarDeck(const char *nomeArquivo, int *quantidadeCartas);

//load
Fonte loadFonte();
void unloadFonte(Fonte fonte);
Molduras loadMolduras();
void unloadMolduras(Molduras molduras);
Textura loadTexturas();
void unloadTexturas(Textura testuras);
void loadIMGCarta(cartas carta[], int quantidadecartas);


#endif