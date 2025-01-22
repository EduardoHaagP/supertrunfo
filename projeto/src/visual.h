#ifndef VISUAL_H
#define VISUAL_H

#include "raylib.h"

typedef enum { MENU = 0, JOGO, DECKS } Estado;

void inicializarJogo(int largura, int altura, const char *titulo);
void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes, const char **opcoes);
void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes);
void desenharTelaJogo();
void desenharTelaDecks();

#endif
