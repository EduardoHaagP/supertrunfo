#include "raylib.h"
#include "visual.h"
#include <stdlib.h>

/*
Color azul = { 53, 114, 151};
Color azulOp = { 53, 114, 151, 0.9};
Color azulClaro = { 134, 184, 215, 1};

Color verde = { 145, 185, 101};
Color verdeOp = { 145, 185, 101, 0.9};
Color verdeClaro = { 171, 239, 97, 1};

Color amarelo = { 240, 188, 65};
Color amareloOp = { 240, 188, 65, 0.9};
Color amareloClaro = { 251, 237, 204, 1};

Color vermelho = {231, 58, 44};
Color vermelhoOp = {231, 58, 44, 0.9};
Color vermelhoClaro = {251, 204, 204, 1};
*/

void inicializarJogo(int largura, int altura, const char *titulo)
{
    InitWindow(largura, altura, titulo);
    SetTargetFPS(60);
}

void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes)
{
    if (IsKeyPressed(KEY_DOWN))
        (*opcaoSelecionada)++;
    if (IsKeyPressed(KEY_UP))
        (*opcaoSelecionada)--;

    if (*opcaoSelecionada < 0)
        *opcaoSelecionada = 2;
    if (*opcaoSelecionada > 2)
        *opcaoSelecionada = 0;

    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 3; i++)
    {
        if (CheckCollisionPointRec(mousePos, botoes[i]))
        {
            *opcaoSelecionada = i;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (i == 0)
                    *estadoAtual = JOGO;
                else if (i == 1)
                    *estadoAtual = DECKS;
                else if (i == 2)
                {
                    CloseWindow();
                    exit(0);
                }
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (*opcaoSelecionada == 0)
            *estadoAtual = JOGO;
        else if (*opcaoSelecionada == 1)
            *estadoAtual = DECKS;
        else if (*opcaoSelecionada == 2)
        {
            CloseWindow();
            exit(0);
        }
    }
}

void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes)
{
    DrawText("Menu Principal", 320, 100, 30, DARKGRAY);
    for (int i = 0; i < 3; i++)
    {
        Color cor = (i == opcaoSelecionada) ? RED : BLACK;
        DrawRectangleRec(botoes[i], LIGHTGRAY);
        DrawText(opcoes[i], botoes[i].x + 10, botoes[i].y + 5, 20, cor);
    }
}

void desenharTelaJogo()
{
    DrawText("Você está jogando!", 280, 200, 30, DARKGREEN);
    DrawText("Pressione ESC para voltar ao menu", 220, 250, 20, GRAY);
}



Molduras LoadMolduras() {
    Molduras molduras;

    // Carrega as imagens e converte para texturas
    Image azul = LoadImage("./assets/moldura/azul.png");
    molduras.azul = LoadTextureFromImage(azul);
    UnloadImage(azul);

    Image verde = LoadImage("./assets/moldura/verde.png");
    molduras.verde = LoadTextureFromImage(verde);
    UnloadImage(verde);

    Image amarelo = LoadImage("./assets/moldura/amarelo.png");
    molduras.amarelo = LoadTextureFromImage(amarelo);
    UnloadImage(amarelo);

    Image vermelha = LoadImage("./assets/moldura/vermelho.png");
    molduras.vermelha = LoadTextureFromImage(vermelha);
    UnloadImage(vermelha);

    return molduras;
}

void UnloadMolduras(Molduras molduras) {
    UnloadTexture(molduras.azul);
    UnloadTexture(molduras.verde);
    UnloadTexture(molduras.amarelo);
    UnloadTexture(molduras.vermelha);
}

void desenharCarta(cartas carta, int x, int y, Molduras molduras) {
    switch (carta.letra) {
        case 'A':
            DrawTextureEx(molduras.azul, (Vector2){x, y}, 0.0f, 0.8f, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verde, (Vector2){x, y}, 0.0f, 0.8f, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amarelo, (Vector2){x, y}, 0.0f, 0.8f, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelha, (Vector2){x, y}, 0.0f, 0.8f, WHITE);
            break;
        default:
            break;
    }
}


void desenharTelaDecks(cartas *listaCartas, int quantidadeCartas)
{


    const int larguraCarta = 204;
    const int alturaCarta = 325;
    const int espacamento = 15;

    const int cartasPorLinha = 4;
    int totalLinhas = (quantidadeCartas + cartasPorLinha - 1) / cartasPorLinha;

    // Calcular altura do conteúdo com base no número de cartas
    int alturaConteudo = totalLinhas * (alturaCarta + espacamento);

    int offsetY = 0; // Controle de scroll vertical

    while (!WindowShouldClose())
    {
        // Controle do scroll usando o mouse ou o teclado
        if (IsKeyDown(KEY_DOWN))
            offsetY -= 10;
        if (IsKeyDown(KEY_UP))
            offsetY += 10;
        if (GetMouseWheelMove() != 0)
            offsetY += GetMouseWheelMove() * 20;

        // Limitar o scroll para não ultrapassar os limites
        if (offsetY > 0)
            offsetY = 0;
        if (offsetY < -alturaConteudo + alturaTela - 50)
            offsetY = -alturaConteudo + alturaTela - 50;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenhar o título (fixo no topo)
        Molduras molduras = LoadMolduras();
        // Desenhar as cartas com o offset de rolagem
        for (int i = 0; i < quantidadeCartas; i++)
        {
            int linha = i / cartasPorLinha;
            int coluna = i % cartasPorLinha;

            int posX = espacamento + coluna * (larguraCarta + espacamento);
            int posY = 61 + linha * (alturaCarta + espacamento) + offsetY;

            // Desenhar cada carta
            desenharCarta(listaCartas[i], posX, posY,molduras);
        }

        DrawRectangle(0, 0, larguraTela, 50, WHITE);
        DrawRectangleLines(0, 0, larguraTela, 50, DARKBLUE);
        DrawText("Biblioteca de Cartas", 10, 15, 20, DARKBLUE);

        EndDrawing();
    }
}
