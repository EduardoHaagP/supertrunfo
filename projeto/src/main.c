#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"
#include "visual.h"
#include "raylib.h"

const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int quantidadeCartas;
    cartas *deck = carregarDeck("deck.csv", &quantidadeCartas);

    const char *opcoes[] = {"Jogar", "Decks", "Sair"};
    Rectangle botoes[3] = {
        {350, 200, 100, 30},
        {350, 240, 100, 30},
        {350, 280, 100, 30}
    };

    int opcaoSelecionada = 0;
    Estado estadoAtual = MENU;

    inicializarJogo(LARGURA_TELA, ALTURA_TELA, "Menu com Raylib");

    Molduras molduras = loadMolduras();
    loadIMGCartas(deck, quantidadeCartas);
    Fonte fonte = loadFonte();
    Textura textura = loadTexturas();


    while (estadoAtual != SAIR) {

        // Atualização lógica com base no estado
        if (estadoAtual == MENU) {
            atualizarMenu(&opcaoSelecionada, &estadoAtual, botoes);
        } else if (estadoAtual == DECKS) {
            desenharTelaDecks(&deck, &quantidadeCartas, molduras, fonte, textura, &estadoAtual);
            if (IsKeyPressed(KEY_ESCAPE)) {
                printf("ESC Pressed in DECKS, changing state to MENU\n");
                estadoAtual = MENU;
            }
        } else if (estadoAtual == JOGO) {
            desenharTelaJogo();
             if (IsKeyPressed(KEY_ESCAPE)) {
                printf("ESC Pressed in JOGO, changing state to MENU\n");
                estadoAtual = MENU;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenhar telas com base no estado
        if (estadoAtual == MENU) {
            desenharMenu(opcaoSelecionada, botoes, opcoes);
        } else if (estadoAtual == JOGO) {
            desenharTelaJogo();
        } else if (estadoAtual == DECKS) {
            desenharTelaDecks(&deck, &quantidadeCartas, molduras, fonte, textura, &estadoAtual);
        }

        EndDrawing();
    }

    // Descarregar recursos antes de fechar o jogo
    for (int i = 0; i < quantidadeCartas; i++) {
        UnloadTexture(deck[i].img);
    }
    unloadTexturas(textura);
    unloadFonte(fonte);
    unloadMolduras(molduras);
    free(deck);

    CloseWindow();
    return 0;
}