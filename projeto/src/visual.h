#ifndef VISUAL_H
#define VISUAL_H

#include "raylib.h"
#include "funcoes.h"

extern const float ESCALA;

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





typedef enum { MENU = 0, JOGO, DECKS } Estado;

void inicializarJogo(int largura, int altura, const char *titulo);
void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes);
void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes);
void desenharTelaJogo();

void loadIMGCarta(cartas carta[], int quantidadecartas);

Fonte loadFonte();
void unloadFonte(Fonte fonte);

Molduras loadMolduras();
void unloadMolduras(Molduras molduras);

void desenharCarta(cartas carta, int x, int y, Molduras molduras, Fonte fonte);

Textura loadTexturas();
void unloadTexturas(Textura testuras);

void desenharTelaDecks(cartas *listaCartas, int quantidadeCartas, Molduras molduras, Fonte fonte,Textura texturas, Estado *estadoAtual);


#endif
