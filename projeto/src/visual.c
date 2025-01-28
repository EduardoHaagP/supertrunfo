#include "raylib.h"
#include "visual.h"
#include <stdlib.h>
#include <string.h>

// Global variable to store the scroll offset for deck screen
static int offsetY = 0;

void inicializarJogo(int largura, int altura, const char *titulo) {
    InitWindow(largura, altura, titulo);
    SetTargetFPS(60);
}

void atualizarMenu(int *opcaoSelecionada, Estado *estadoAtual, Rectangle *botoes) {
    if (IsKeyPressed(KEY_DOWN))
        (*opcaoSelecionada)++;
    if (IsKeyPressed(KEY_UP))
        (*opcaoSelecionada)--;

    if (*opcaoSelecionada < 0)
        *opcaoSelecionada = 2;
    if (*opcaoSelecionada > 2)
        *opcaoSelecionada = 0;

    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        if (CheckCollisionPointRec(mousePos, botoes[i])) {
            *opcaoSelecionada = i;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 0)
                    *estadoAtual = JOGO;
                else if (i == 1)
                    *estadoAtual = DECKS;
                else if (i == 2) {
                    CloseWindow();
                    exit(0);
                }
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (*opcaoSelecionada == 0)
            *estadoAtual = JOGO;
        else if (*opcaoSelecionada == 1)
            *estadoAtual = DECKS;
        else if (*opcaoSelecionada == 2) {
            CloseWindow();
            exit(0);
        }
    }
}

void desenharMenu(int opcaoSelecionada, Rectangle *botoes, const char **opcoes) {
    ClearBackground(RAYWHITE);
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

Fonte loadFonte() {
    Fonte fonte;
    fonte.tituloCartas = LoadFont("./assets/font/Avenir-Black.ttf");
    fonte.tituloTelas = LoadFont("./assets/font/Avenir-Book.ttf");
    fonte.letraCarta = LoadFont("./assets/font/Avenir-Heavy.ttf");
    fonte.atributoCartas = LoadFont("./assets/font/AvenirNextCyr-Medium.ttf");
    return fonte;
}

void unloadFonte(Fonte font) {
    UnloadFont(font.tituloCartas);
    UnloadFont(font.tituloTelas);
    UnloadFont(font.letraCarta);
    UnloadFont(font.atributoCartas);
    return;
}

Molduras loadMolduras() {
    Molduras molduras;

    // Carrega as imagens e converte para texturas
    Image azul = LoadImage("./assets/moldura/azul.png");
    molduras.azul = LoadTextureFromImage(azul);
    UnloadImage(azul);

    Image azulST = LoadImage("./assets/moldura/azulST.png");
    molduras.azulST = LoadTextureFromImage(azulST);
    UnloadImage(azulST);

    Image verde = LoadImage("./assets/moldura/verde.png");
    molduras.verde = LoadTextureFromImage(verde);
    UnloadImage(verde);

    Image verdeST = LoadImage("./assets/moldura/verdeST.png");
    molduras.verdeST = LoadTextureFromImage(verdeST);
    UnloadImage(verdeST);

    Image amarelo = LoadImage("./assets/moldura/amarelo.png");
    molduras.amarelo = LoadTextureFromImage(amarelo);
    UnloadImage(amarelo);

    Image amareloST = LoadImage("./assets/moldura/amareloST.png");
    molduras.amareloST = LoadTextureFromImage(amareloST);
    UnloadImage(amareloST);

    Image vermelho = LoadImage("./assets/moldura/vermelho.png");
    molduras.vermelho = LoadTextureFromImage(vermelho);
    UnloadImage(vermelho);

    Image vermelhoST = LoadImage("./assets/moldura/vermelhoST.png");
    molduras.vermelhoST = LoadTextureFromImage(vermelhoST);
    UnloadImage(vermelhoST);

    return molduras;
}

void unloadMolduras(Molduras molduras) {
    UnloadTexture(molduras.azul);
    UnloadTexture(molduras.verde);
    UnloadTexture(molduras.amarelo);
    UnloadTexture(molduras.vermelho);
    UnloadTexture(molduras.azulST);
    UnloadTexture(molduras.verdeST);
    UnloadTexture(molduras.amareloST);
    UnloadTexture(molduras.vermelhoST);
}

void escreverAtributoCartas(cartas carta, int x, int y, Fonte fonte) {
    char bufferAno[20]; // Buffer para armazenar o ano como string
    sprintf(bufferAno, "%d", carta.anoConstrucao);
    DrawTextEx(fonte.atributoCartas, "Ano de Construcao", (Vector2){x + (17 * ESCALA), y + (201 * ESCALA)}, 16 * ESCALA, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferAno, (Vector2){x + (155 * ESCALA), y + (201 * ESCALA)}, 16 * ESCALA, 0, WHITE);

    char bufferAltura[20]; // Buffer para armazenar o ano como string
    sprintf(bufferAltura, "%d", carta.altura);
    DrawTextEx(fonte.atributoCartas, "Altura", (Vector2){x + (17 * ESCALA), y + ((201 + 22) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferAltura, (Vector2){x + (155 * ESCALA), y + ((201 + 22) * ESCALA)}, 16 * ESCALA, 0, WHITE);

    DrawTextEx(fonte.atributoCartas, "Visitas Anuais", (Vector2){x + (17 * ESCALA), y + ((201 + 44) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    if (carta.visitasAnuais > 1000000000) // bilhao
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000000000, " Bi");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * ESCALA), y + ((201 + 44) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    }
    else if (carta.visitasAnuais > 1000000) // milhao
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000000, " M");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * ESCALA), y + ((201 + 44) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    }
    else if (carta.visitasAnuais > 1000) // mil
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000, " m");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * ESCALA), y + ((201 + 44) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    }
    else
    {
        char resultado[50];
        sprintf(resultado, "%d", (carta.visitasAnuais));
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * ESCALA), y + ((201 + 44) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    }

    char bufferImpotanciaHistorica[20]; // Buffer para armazenar o ano como string
    sprintf(bufferImpotanciaHistorica, "%d", carta.importanciaHistorica);
    DrawTextEx(fonte.atributoCartas, "Importancia historica", (Vector2){x + (17 * ESCALA), y + ((201 + 66) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferImpotanciaHistorica, (Vector2){x + (155 * ESCALA), y + ((201 + 66) * ESCALA)}, 16 * ESCALA, 0, WHITE);

    char bufferPopularidade[20]; // Buffer para armazenar o ano como string
    sprintf(bufferPopularidade, "%d", carta.popularidade);
    DrawTextEx(fonte.atributoCartas, "Popularidade", (Vector2){x + (17 * ESCALA), y + ((201 + 88) * ESCALA)}, 16 * ESCALA, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferPopularidade, (Vector2){x + (155 * ESCALA), y + ((201 + 88) * ESCALA)}, 16 * ESCALA, 0, WHITE);
}

void loadIMGCarta(cartas carta[], int quantidadecartas) {
    for (int i = 0; i < quantidadecartas; i++) {
        carta[i].img = LoadTexture(carta[i].arqimg);

        if (carta[i].img.id == 0) {
            // Handle the error (e.g., log it, return a default texture, etc.)
            printf("Failed to load texture: %s\n", carta[i].nome);
            // Optionally return a default texture or an empty texture
        }
    }

    // Check if the texture was loaded successfully

    return;
}

void desenharCarta(cartas carta, int x, int y, Molduras molduras, Fonte fonte) {
    DrawTextureEx(carta.img, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
    if (carta.supertrunfo == 1) {
        switch (carta.letra) {
        case 'A':

            DrawTextureEx(molduras.azulST, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verdeST, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amareloST, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelhoST, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        default:
            break;
        }
    } else {
        switch (carta.letra) {
        case 'A':
            DrawTextureEx(molduras.azul, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verde, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amarelo, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelho, (Vector2){x, y}, 0.0f, ESCALA, WHITE);
            break;
        default:
            break;
        }
    }
    Vector2 posicaoNome = (Vector2){x + (60 * ESCALA), y + (13 * ESCALA)};
    DrawTextEx(fonte.tituloCartas, carta.nome, posicaoNome, 16 * ESCALA, 0, WHITE);
    escreverAtributoCartas(carta, x, y, fonte);
}

Textura loadTexturas(){
    Textura texturas;
    texturas.setaOFF = LoadTexture("./assets/textura/setasaidaOFF.png");
    texturas.setaON = LoadTexture("./assets/textura/setasaidaON.png");
    texturas.TexturaFundo = LoadTexture("./assets/textura/vector.png");
    
    return texturas;
    
}
void unloadTexturas(Textura texturas){
    UnloadTexture(texturas.setaOFF);
    UnloadTexture(texturas.setaON);
    UnloadTexture(texturas.TexturaFundo);
    return;
};


void desenharTelaDecks(cartas *listaCartas, int quantidadeCartas, Molduras molduras, Fonte fonte, Textura texturas, Estado *estadoAtual)
{
    const int ALTURA = 600;
    const int LARGURA = 800;
    const int larguraCarta = 155;
    const int alturaCarta = 248;
    const int espacamentoX = 23;
    const int espacamentoY = 20;
    const int extremosLaterais = 54;

    const int cartasPorLinha = 4;

    int totalLinhas = (quantidadeCartas + cartasPorLinha - 1) / cartasPorLinha; // Arredonda para cima
    int alturaConteudo = totalLinhas * (alturaCarta + espacamentoY + 20);

    // Clipping Rectangle - Define the area where cards should be visible
    Rectangle clippingRec = {0, 62, LARGURA, ALTURA - 62}; 

    // Control scroll
    if (IsKeyDown(KEY_DOWN))
        offsetY -= 20;
    if (IsKeyDown(KEY_UP))
        offsetY += 20;
    if (GetMouseWheelMove() != 0)
        offsetY += GetMouseWheelMove() * 20;

    // Limitar o scroll
    if (offsetY > 0)
        offsetY = 0;
    if (offsetY < -alturaConteudo + ALTURA - 50)
        offsetY = -alturaConteudo + ALTURA - 50;

    DrawTextureEx(texturas.TexturaFundo, (Vector2){0, 0}, 0.0f, 1.5, WHITE);
   
   
    BeginScissorMode(clippingRec.x, clippingRec.y, clippingRec.width, clippingRec.height);

    // Desenhar cartas
    for (int i = 0; i < quantidadeCartas; i++) {
        int linha = i / cartasPorLinha;
        int coluna = i % cartasPorLinha;

        int posX;
        if (coluna == 0) {
            // Primeira coluna com espaçamento lateral maior
            posX = extremosLaterais;
        } else {
            // Outras colunas
            posX = extremosLaterais + coluna * (larguraCarta + espacamentoX);
        }

        int posY = 82 + (linha * (alturaCarta + espacamentoY)) + offsetY;

        desenharCarta(listaCartas[i], posX, posY, molduras, fonte);
    }
    
    EndScissorMode();
    
    DrawRectangle(0, 28, LARGURA, 34, WHITE);
    DrawRectangleLinesEx((Rectangle){0, 28, LARGURA, 34}, 0.8f, (Color){175, 215, 248, 255});
    DrawCircleV((Vector2){46, 45}, 13, WHITE);
    
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointCircle(mousePos, (Vector2){46, 45}, 13))
    {
        DrawTexture(texturas.setaON, 33, 32, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           *estadoAtual = MENU; // Returns to menu.
            offsetY = 0; // Reset scroll offset when exiting deck screen.
        }
    }
    else
    {
        DrawTexture(texturas.setaOFF, 33, 32, WHITE);
    }

    DrawTextEx(fonte.tituloTelas, "Biblioteca de Cartas", (Vector2){70, 32}, 25, 0, BLACK);
}
