#ifndef VISUAL_H
#define VISUAL_H

#include "raylib.h"
#include "funcoes.h"

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

extern int larguraTela;  // Declare as extern
extern int alturaTela;   // Declare as extern


typedef enum { MENU = 0, JOGO, DECKS } Estado;

void inicializarJogo(int largura, int altura, const char *titulo);
void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes);
void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes);
void desenharTelaJogo();
Molduras LoadMolduras();
void UnloadMolduras(Molduras molduras);
void desenharCarta(cartas carta, int x, int y, Molduras molduras);
void desenharTelaDecks(cartas *deck, int quantidadeCartas, Molduras moldura);


#endif
