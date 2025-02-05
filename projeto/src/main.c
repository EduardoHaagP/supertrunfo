#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "compara.h"
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
    Image icon = LoadImage("assets/icon.png");

    inicializarJogo(LARGURA_TELA, ALTURA_TELA, "Super Trunfo Pontos Turisticos");
    SetWindowIcon(icon);

    SetExitKey(KEY_NULL);

    Molduras molduras = loadMolduras();
    loadIMGCartas(deck, quantidadeCartas);
    Fonte fonte = loadFonte();
    Textura textura = loadTexturas();

    cartas minhaCarta;
    cartas cartaInimigo;
    bool novaRodada = true;

    while (!WindowShouldClose()) {
        // Atualização lógica baseada no estado
        if (estadoAtual == MENU) {
            atualizarMenu(&opcaoSelecionada, &estadoAtual, botoes);
        } else if (estadoAtual == DECKS) {
            if(IsKeyPressed(KEY_ESCAPE)){
                estadoAtual = MENU;
             }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(textura.TexturaFundo, (Vector2){0, 0}, 0.0f, 1.5, WHITE);


        // Desenhar telas com base no estado
        if (estadoAtual == MENU) {
            desenharMenu(opcaoSelecionada, botoes, opcoes);
        } else if (estadoAtual == JOGO) {

            if (novaRodada) {
                minhaCarta = deck[rand() % quantidadeCartas];
                cartaInimigo = deck[rand() % quantidadeCartas];
                novaRodada = false;
            }

            desenharTelaJogo(minhaCarta, cartaInimigo, molduras, fonte);//

            if (IsKeyPressed(KEY_SPACE)) { // Espera o jogador pressionar ESPAÇO
                novaRodada = true; // Começa uma nova rodada
            }

            // Verificar se ESC retorna ao menu
            if (IsKeyPressed(KEY_ESCAPE)) {
                estadoAtual = MENU;
                novaRodada = true; // Reinicia o jogo
            }
        } else if (estadoAtual == DECKS) {
             // Passar estado por referência para permitir alteração dentro da função
            desenharTelaDecks(&deck, &quantidadeCartas, molduras, fonte, textura, &estadoAtual);
        } else if (estadoAtual == SAIR){
            break;
        }


        EndDrawing(); 
    }

    for (int i = 0; i < quantidadeCartas; i++) {
        UnloadTexture(deck[i].img);
    }
    UnloadImage(icon);
    unloadTexturas(textura);
    unloadFonte(fonte);
    unloadMolduras(molduras);
    free(deck);
    CloseWindow();
    return 0;
}