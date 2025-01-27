#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"
#include "visual.h"
#include "raylib.h"


const float ESCALA = 155.37/204; 
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
    loadIMGCarta(deck, quantidadeCartas);    
    Fonte fonte = loadFonte();
    

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
            desenharTelaDecks(deck,quantidadeCartas, molduras,fonte);
            if (IsKeyPressed(KEY_ESCAPE)) estadoAtual = MENU;
        }

        EndDrawing();
    }

    for (int i = 0; i < quantidadeCartas; i++)
    {
        UnloadTexture(deck[i].img);
    }
    
    unloadFonte(fonte);
    unloadMolduras(molduras);
    CloseWindow();
    free(deck);
    return 0;
}