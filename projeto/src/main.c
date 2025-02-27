#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"
#include "visual.h"
#include "raylib.h"
#include <time.h>

const int LARGURA_TELA = 800;
const int ALTURA_TELA = 600;

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int quantidadeCartas;
    cartas *deck;

    deck = carregarDeckBinario("deck.bin", &quantidadeCartas);

    if (deck == NULL){
        printf("Bem-vindo ao Super Trunfo: Pontos Turísticos!\n");
        deck = carregarDeck ("deck.csv", &quantidadeCartas);
    }

    srand(time(NULL));

    const char *opcoes[] = {"Jogar", "Decks", "Sair"};
    Rectangle botoes[3] = {
        {350, 200, 100, 30},
        {350, 240, 100, 30},
        {350, 280, 100, 30}};

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
    bool vezJogador = true;
    int cartasJogador;
    if (quantidadeCartas % 2 == 1)
    {
        cartasJogador = (quantidadeCartas / 2) + 1;
    }
    else
    {
        cartasJogador = (quantidadeCartas / 2);
    }

    int cartasComputador = quantidadeCartas / 2;
    int atributoEscolhido = -1;
    bool novaRodada = true;
    const char *resultado = "";

    while (!WindowShouldClose())
    {
        // Atualização lógica baseada no estado
        if (estadoAtual == MENU)
        {
            atualizarMenu(&opcaoSelecionada, &estadoAtual, botoes);
        }
        else if (estadoAtual == DECKS)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                estadoAtual = MENU;
            }
        }
        else if (estadoAtual == RESULTADO_BATALHA)
        {
            if(IsKeyPressed(KEY_ESCAPE))
            {
                estadoAtual = MENU;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(textura.TexturaFundo, (Vector2){0, 0}, 0.0f, 1.5, WHITE);

        // Desenhar telas com base no estado
        if (estadoAtual == MENU)
        {
            desenharMenu(opcaoSelecionada, botoes, opcoes);
        }
        else if (estadoAtual == JOGO)
        {
            if (novaRodada)
            {
                minhaCarta = deck[rand() % quantidadeCartas];
                cartaInimigo = deck[rand() % quantidadeCartas];
                novaRodada = false;
                resultado = "";
                atributoEscolhido = -1;
            }

            if (vezJogador)
            {
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
                    "5 - Popularidade"};

                Vector2 mousePos = GetMousePosition();

                for (int i = 0; i < 5; i++)
                {
                    int largura = (i == 3) ? 280 : 250;
                    int altura = 40;
                    int posX = 50;
                    int posY = 170 + (i * 50);

                    caixasAtributos[i] = (Rectangle){posX, posY, largura, altura};

                    Color corCaixa = (Color){230, 230, 230, 255};
                    Color corBorda = (Color){180, 180, 180, 255};

                    if (CheckCollisionPointRec(mousePos, caixasAtributos[i]))
                    {
                        corCaixa = (Color){200, 200, 200, 255};
                        corBorda = (Color){150, 150, 150, 255};

                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                        {
                            atributoEscolhido = i;
                            estadoAtual = RESULTADO_BATALHA;
                        }
                    }

                    DrawRectangle(caixasAtributos[i].x + 3, caixasAtributos[i].y + 3, caixasAtributos[i].width, caixasAtributos[i].height, (Color){0, 0, 0, 50});

                    DrawRectangleRec(caixasAtributos[i], corCaixa);
                    DrawRectangleLinesEx(caixasAtributos[i], 2, corBorda);

                    DrawText(atributos[i], caixasAtributos[i].x + 15, caixasAtributos[i].y + 10, 20, DARKGRAY);
                }
            }
            else
            {
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
        }
        else if (estadoAtual == RESULTADO_BATALHA)
        {
            int valorJogador = 0;
            int valorComputador = 0;
            if (atributoEscolhido == 0){
              valorComputador = cartaInimigo.anoConstrucao;
              valorJogador = minhaCarta.anoConstrucao;  
            }
            if (atributoEscolhido == 1){
              valorComputador = cartaInimigo.altura;
              valorJogador = minhaCarta.altura;  
            }
            if (atributoEscolhido == 2){
              valorComputador = cartaInimigo.visitasAnuais;
              valorJogador = minhaCarta.visitasAnuais;  
            }
            if (atributoEscolhido == 3) {
              valorComputador = cartaInimigo.importanciaHistorica;
              valorJogador = minhaCarta.importanciaHistorica;  
            }
            if (atributoEscolhido == 4) {
              valorComputador = cartaInimigo.popularidade;
              valorJogador = minhaCarta.popularidade;  
            }

            



            desenharTelaJogo(minhaCarta, cartaInimigo, molduras, fonte);

            if (valorJogador > valorComputador)
            {
                cartasJogador++;
                cartasComputador--;
                resultado = "Você ganhou!";
            }
            else if (valorJogador < valorComputador)
            {
                cartasJogador--;
                cartasComputador++;
                resultado = "Você perdeu!";
            }
            else
            {
                resultado = "Empate!";
            }

            int larguraResultado = MeasureText(resultado, 30);
            DrawText(resultado, (800 - larguraResultado) / 2, 520, 30, RED);

            DrawText("Pressione ESPAÇO para continutar", 300, 600, 20, DARKGRAY);
            if (IsKeyPressed(KEY_SPACE))
            {
                if (cartasJogador == 32 || cartasComputador == 32)
                {
                    estadoAtual = FIM_JOGO;
                }
                else
                {
                    estadoAtual = JOGO;
                    novaRodada = true;
                    vezJogador = !vezJogador;
                }
            }
        }
        else if (estadoAtual == FIM_JOGO)
        {
            if (cartasJogador == 32)
            {
                DrawText("Parabéns, você venceu o jogo!", 300, 250, 30, GREEN);
            }
            else
            {
                DrawText("Você perdeu o jogo!", 300, 250, 30, RED);
            }

            DrawText("Pressione ENTER para voltar ao menu", 250, 500, 20, DARKGRAY);
            if (IsKeyPressed(KEY_ENTER))
            {
                estadoAtual = MENU;
                cartasJogador = 16; // número de cartas inicial
                cartasComputador = 16;
            }
        }
        else if (estadoAtual == DECKS)
        {
            // Passar estado por referência para permitir alteração dentro da função
            desenharTelaDecks(&deck, &quantidadeCartas, molduras, fonte, textura, &estadoAtual);
        }
        else if (estadoAtual == SAIR)
        {
            break;
        }

        EndDrawing();
    }

    salvarDeckBinario(deck, quantidadeCartas, "deck.bin");

    for (int i = 0; i < quantidadeCartas; i++)
    {
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