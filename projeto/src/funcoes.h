#ifndef FUNCOES_H
#define FUNCOES_H

#include "cartas.h" // Inclui a definição da estrutura cartas

void jogar();
void menu(int *vmenu);
void menuDecks(cartas **deck, int *quantidadeCartas);
int contarcartas(FILE *arq);
cartas configuracoesIniciais(FILE *arq);

#endif // FUNCOES_H