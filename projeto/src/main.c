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
    int vezJogador = 1; 
    int cartasJogador = 16;  
    int cartasComputador = 16;
    int atributoEscolhido = -1;
    bool novaRodada = true;
    const char *resultado = "";
    

while (!WindowShouldClose()) {
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

    if (estadoAtual == MENU) {
        desenharMenu(opcaoSelecionada, botoes, opcoes);
    } 
else if (estadoAtual == JOGO) {
    if (novaRodada) {
        minhaCarta = deck[rand() % quantidadeCartas];
        cartaInimigo = deck[rand() % quantidadeCartas];
        novaRodada = false;
        resultado = "";
        atributoEscolhido = -1;  
    }

    if (vezJogador) {
        int cartaPosX = LARGURA_TELA - 300;  
        int cartaPosY = 150;                 
        desenharCarta(minhaCarta, cartaPosX, cartaPosY, molduras, fonte, 1.0f, false);

        DrawText("Escolha um atributo:", 50, 100, 20, DARKGRAY);

        Rectangle caixasAtributos[5];
        const char *atributos[] = {
            "1 - Ano de Construção",
            "2 - Altura",
            "3 - Visitas Anuais",
            "4 - Importância Histórica",
            "5 - Popularidade"
        };

        Vector2 mousePos = GetMousePosition(); 

        for (int i = 0; i < 5; i++) {
            int largura = (i == 3) ? 280 : 250; 
            int altura = 40;                    
            int posX = 50;                       
            int posY = 170 + (i * 50);           

            caixasAtributos[i] = (Rectangle){posX, posY, largura, altura}; 

            
            Color corCaixa = (Color){230, 230, 230, 255};  
            Color corBorda = (Color){180, 180, 180, 255};  

            
            if (CheckCollisionPointRec(mousePos, caixasAtributos[i])) {
                corCaixa = (Color){200, 200, 200, 255};  
                corBorda = (Color){150, 150, 150, 255};  

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    atributoEscolhido = i; 
                    estadoAtual = RESULTADO_BATALHA;  
                }
            }

            DrawRectangle(caixasAtributos[i].x + 3, caixasAtributos[i].y + 3, caixasAtributos[i].width, caixasAtributos[i].height, (Color){0, 0, 0, 50});

            DrawRectangleRec(caixasAtributos[i], corCaixa);
            DrawRectangleLinesEx(caixasAtributos[i], 2, corBorda); 

            DrawText(atributos[i], caixasAtributos[i].x + 15, caixasAtributos[i].y + 10, 20, DARKGRAY);
        }
    } else {
        int larguraTexto = MeasureText("Oponente escolhe atributo:", 20);
        DrawText("Oponente escolhe atributo:", (LARGURA_TELA - larguraTexto) / 2, 100, 20, DARKGRAY);

        desenharCarta(cartaInimigo, 300, 200, molduras, fonte, 1.0f, false);

        atributoEscolhido = rand() % 5;

        const char *atributos[] = {"1 - Ano de Construção", "2 - Altura", "3 - Visitas Anuais", "4 - Importância Histórica", "5 - Popularidade"};
        larguraTexto = MeasureText(atributos[atributoEscolhido], 20);
        DrawText(atributos[atributoEscolhido], (LARGURA_TELA - larguraTexto) / 2, 130, 20, DARKGRAY);

        EndDrawing();
        BeginDrawing();

        WaitTime(3.0);  

        estadoAtual = RESULTADO_BATALHA;  
    }
}else if (estadoAtual == RESULTADO_BATALHA) {
        desenharTelaJogo (minhaCarta, cartaInimigo, molduras, fonte);

        int valorJogador = obterAtributo (minhaCarta, atributoEscolhido);
        int valorComputador = obterAtributo (cartaInimigo, atributoEscolhido);

        if (valorJogador > valorComputador) {
            cartasJogador++;
            cartasComputador --;
            resultado = "Você ganhou!";
        }else if (valorJogador < valorComputador) {
            cartasJogador --;
            cartasComputador++;
            resultado = "Você perdeu!";
        }else{
            resultado = "Empate!";
        }

    int larguraResultado = MeasureText (resultado, 30);
    DrawText(resultado, (800 - larguraResultado) / 2, 520, 30, RED);

    DrawText("Pressione ESPAÇO para continutar", 300, 600, 20, DARKGRAY);
    if (IsKeyPressed(KEY_SPACE)) {
        if(cartasJogador == 32 || cartasComputador == 32) {
            estadoAtual = FIM_JOGO;
        }else{
            estadoAtual = JOGO;
            novaRodada = true;
            vezJogador = !vezJogador;
        }
    }
    }else if (estadoAtual == FIM_JOGO) {
        if (cartasJogador == 32) {
            DrawText("Parabéns, você venceu o jogo!", 300, 400, 30, GREEN);
        }else{
            DrawText("Você perdeu o jogo!", 300, 400, 30, RED);
            }

            DrawText ("Pressione ENTER para voltar ao menu", 250, 400, 20, DARKGRAY);
            if(IsKeyPressed(KEY_ENTER)){
                estadoAtual = MENU;
                cartasJogador = 16;  //número de cartas inicial
                cartasComputador = 16;
            }
    }else if (estadoAtual == DECKS){
        desenharTelaDecks (&deck, &quantidadeCartas, molduras, fonte, textura, &estadoAtual);
    }

    EndDrawing();
}
}