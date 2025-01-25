#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"
#include "visual.h"
#include "raylib.h"




int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int quantidadeCartas;
    cartas *deck = carregarDeck("deck.csv", &quantidadeCartas);




    const int larguraTela = 800;
    const int alturaTela = 450;
    const char *opcoes[] = {"Jogar", "Decks", "Sair"};
    Rectangle botoes[3] = {
        {350, 200, 100, 30},
        {350, 240, 100, 30},
        {350, 280, 100, 30}
    };

    int opcaoSelecionada = 0;
    Estado estadoAtual = MENU;

    inicializarJogo(larguraTela, alturaTela, "Menu com Raylib");

    while (!WindowShouldClose()) {
        if (estadoAtual == MENU) {
            atualizarMenu(&opcaoSelecionada, &estadoAtual, botoes);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (estadoAtual == MENU) {
            desenharMenu(opcaoSelecionada, botoes, opcoes);
        } else if (estadoAtual == JOGO) {
            desenharTelaJogo();
            if (IsKeyPressed(KEY_ESCAPE)) estadoAtual = MENU;
        } else if (estadoAtual == DECKS) {
            desenharTelaDecks(deck,quantidadeCartas);
            if (IsKeyPressed(KEY_ESCAPE)) estadoAtual = MENU;
        }

        EndDrawing();
    }

    CloseWindow();
    free(deck);
    return 0;
}