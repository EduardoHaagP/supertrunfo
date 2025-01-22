#include "raylib.h"
#include "visual.h"
#include <stdlib.h>


void inicializarJogo(int largura, int altura, const char *titulo) {
    InitWindow(largura, altura, titulo);
    SetTargetFPS(60);
}

void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes, const char **opcoes) {
    if (IsKeyPressed(KEY_DOWN)) (*opcaoSelecionada)++;
    if (IsKeyPressed(KEY_UP)) (*opcaoSelecionada)--;

    if (*opcaoSelecionada < 0) *opcaoSelecionada = 2;
    if (*opcaoSelecionada > 2) *opcaoSelecionada = 0;

    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        if (CheckCollisionPointRec(mousePos, botoes[i])) {
            *opcaoSelecionada = i;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 0) *estadoAtual = JOGO;
                else if (i == 1) *estadoAtual = DECKS;
                else if (i == 2) {
                    CloseWindow();
                    exit(0);
                }
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (*opcaoSelecionada == 0) *estadoAtual = JOGO;
        else if (*opcaoSelecionada == 1) *estadoAtual = DECKS;
        else if (*opcaoSelecionada == 2) {
            CloseWindow();
            exit(0);
        }
    }
}

void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes) {
    DrawText("Menu Principal", 320, 100, 30, DARKGRAY);
    for (int i = 0; i < 3; i++) {
        Color cor = (i == opcaoSelecionada) ? RED : BLACK;
        DrawRectangleRec(botoes[i], LIGHTGRAY);
        DrawText(opcoes[i], botoes[i].x + 10, botoes[i].y + 5, 20, cor);
    }
}

void desenharTelaJogo() {
    DrawText("Você está jogando!", 280, 200, 30, DARKGREEN);
    DrawText("Pressione ESC para voltar ao menu", 220, 250, 20, GRAY);
}

void desenharTelaDecks() {
    DrawText("Tela de Decks", 320, 200, 30, DARKBLUE);
    DrawText("Pressione ESC para voltar ao menu", 220, 250, 20, GRAY);
}