#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include "cartas.h" // Inclui a definição da estrutura cartas
#include "jogar.h"
#include "visual.h"
#include "raylib.h"





int contarcartas(FILE *arq);
cartas configuracoesIniciais(FILE *arq);
cartas *carregarDeck(const char *nomeArquivo, int *quantidadeCartas);



#endif 