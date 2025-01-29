#ifndef VISUAL_H
#define VISUAL_H

#include "raylib.h"
#include "funcoes.h"






typedef enum { MENU = 0, JOGO, DECKS } Estado;

void inicializarJogo(int largura, int altura, const char *titulo);
void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes);
void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes);
void desenharTelaJogo();


void desenharCartaSelecionada(cartas carta, int x, int y, Molduras molduras, Fonte fonte);

void desenharCarta(cartas carta, int x, int y, Molduras molduras, Fonte fonte, float escala, bool isHovered);


void filterAndSortCards(cartas *listaCartas, int quantidadeCartas, cartas **filteredCards, int *filteredCount);
void updateSearchText();

void drawSearchBox(Rectangle rect, Fonte fonte, bool isHovered, bool isActive);

void drawSortByDropdown(Rectangle rect, Fonte fonte);

void drawLetterDropdown(Rectangle rect, Fonte fonte);

void desenharTelaDecks(cartas *listaCartas, int quantidadeCartas, Molduras molduras, Fonte fonte,Textura texturas, Estado *estadoAtual);


#endif
