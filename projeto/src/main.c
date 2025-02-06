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
    int vezJogador = 1; // 1 = jogador, 0 = computador
    int cartasJogador = 10;  // Número inicial de cartas
    int cartasComputador = 10;
    int atributoEscolhido;
    bool novaRodada = true;
    const char *resultado = "";

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
    } 
    else if (estadoAtual == JOGO) {
        // 🔹 INÍCIO DA RODADA: Sorteia cartas apenas uma vez por rodada
        if (novaRodada) {
            minhaCarta = deck[rand() % quantidadeCartas];
            cartaInimigo = deck[rand() % quantidadeCartas];
            novaRodada = false;
            resultado = "";
        }

        desenharTelaJogo(minhaCarta, cartaInimigo, molduras, fonte);

        // ESCOLHA DO ATRIBUTO
        if (vezJogador) { 
            DrawText("Escolha um atributo (1, 2, 3, 4 ou 5)", 250, 500, 20, BLUE);

            if (IsKeyPressed(KEY_ONE)) atributoEscolhido = 0;
            if (IsKeyPressed(KEY_TWO)) atributoEscolhido = 1;
            if (IsKeyPressed(KEY_THREE)) atributoEscolhido = 2;
            if (IsKeyPressed(KEY_FOUR)) atributoEscolhido = 3;
            if (IsKeyPressed(KEY_FIVE)) atributoEscolhido = 4;



            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_FOUR)|| IsKeyPressed(KEY_FIVE)) {
                vezJogador = 0; 
            }
        } else { 
            atributoEscolhido = rand() % 3;
            vezJogador = 1; 
        }

        // 🔹 COMPARAÇÃO DAS CARTAS
        if (atributoEscolhido != -1) { // Se um atributo já foi escolhido
            int valorJogador = obterAtributo(minhaCarta, atributoEscolhido);
            int valorComputador = obterAtributo(cartaInimigo, atributoEscolhido);

            if (valorJogador > valorComputador) {
                cartasJogador++;
                cartasComputador--;
                resultado = "Você venceu!";
            } else if (valorJogador < valorComputador) {
                cartasJogador--;
                cartasComputador++;
                resultado = "Você perdeu!";
            } else {
                resultado = "Empate!";
            }

            // Exibir o resultado no final da rodada
            int larguraResultado = MeasureText(resultado, 30);
            DrawText(resultado, (800 - larguraResultado) / 2, 520, 30, RED);
        }

        // CONTINUAR OU FINALIZAR O JOGO
        if (IsKeyPressed(KEY_SPACE)) { // Pressionar espaço avança para a próxima rodada
            novaRodada = true;
            atributoEscolhido = -1;
        }

        //  FIM 
        if (cartasJogador == 0 || cartasComputador == 0) {
            estadoAtual = FIM_JOGO;
        }

        // ESC para sair 
        if (IsKeyPressed(KEY_ESCAPE)) {
            estadoAtual = MENU;
            novaRodada = true;
        }
    }
    else if (estadoAtual == FIM_JOGO) {
        if (cartasJogador > 0) {
            DrawText("Parabéns, você venceu!", 280, 200, 30, GREEN);
        } else {
            DrawText("O computador venceu!", 280, 200, 30, RED);
        }
        DrawText("Pressione ENTER para voltar ao menu", 250, 400, 20, GRAY);
        if (IsKeyPressed(KEY_ENTER)) estadoAtual = MENU;
    }
    else if (estadoAtual == DECKS) {
        desenharTelaDecks(&deck, &quantidadeCartas, molduras, fonte, textura, &estadoAtual);
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