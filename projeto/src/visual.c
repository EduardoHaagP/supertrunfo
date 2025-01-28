#include "raylib.h"
#include "visual.h"
#include <stdlib.h>
#include <string.h>

// Global variable to store the scroll offset for deck screen
static int offsetY = 0;
// Global variable to store the index of the currently selected card
static int selectedCardIndex = -1;

static float escalaPadrao = 155.37 / 204; // Escala padrão para as cartas na lista.
static float escalaReduzida = 115.0 / 204; // Escala reduzida para cartas não selecionadas
static float escalaGrande = 6800/5179;  // escala para carta em destaque
static int scrollSpeedPadrao = 20; //velocidade do scroll em tamanho padrão
static int scrollSpeedReduzido = 15; //velocidade do scroll em tamanho reduzido

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



void escreverAtributoCartas(cartas carta, int x, int y, Fonte fonte, float escala) {
    char bufferAno[20]; // Buffer para armazenar o ano como string
    sprintf(bufferAno, "%d", carta.anoConstrucao);
    DrawTextEx(fonte.atributoCartas, "Ano de Construcao", (Vector2){x + (17 * escala), y + (201 * escala)}, 16 * escala, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferAno, (Vector2){x + (155 * escala), y + (201 * escala)}, 16 * escala, 0, WHITE);

    char bufferAltura[20]; // Buffer para armazenar o ano como string
    sprintf(bufferAltura, "%d", carta.altura);
    DrawTextEx(fonte.atributoCartas, "Altura", (Vector2){x + (17 * escala), y + ((201 + 22) * escala)}, 16 * escala, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferAltura, (Vector2){x + (155 * escala), y + ((201 + 22) * escala)}, 16 * escala, 0, WHITE);

    DrawTextEx(fonte.atributoCartas, "Visitas Anuais", (Vector2){x + (17 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, WHITE);
    if (carta.visitasAnuais > 1000000000) // bilhao
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000000000, " Bi");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, WHITE);
    }
    else if (carta.visitasAnuais > 1000000) // milhao
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000000, " M");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, WHITE);
    }
    else if (carta.visitasAnuais > 1000) // mil
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000, " m");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, WHITE);
    }
    else
    {
        char resultado[50];
        sprintf(resultado, "%d", (carta.visitasAnuais));
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, WHITE);
    }

    char bufferImpotanciaHistorica[20]; // Buffer para armazenar o ano como string
    sprintf(bufferImpotanciaHistorica, "%d", carta.importanciaHistorica);
    DrawTextEx(fonte.atributoCartas, "Importancia historica", (Vector2){x + (17 * escala), y + ((201 + 66) * escala)}, 16 * escala, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferImpotanciaHistorica, (Vector2){x + (155 * escala), y + ((201 + 66) * escala)}, 16 * escala, 0, WHITE);

    char bufferPopularidade[20]; // Buffer para armazenar o ano como string
    sprintf(bufferPopularidade, "%d", carta.popularidade);
    DrawTextEx(fonte.atributoCartas, "Popularidade", (Vector2){x + (17 * escala), y + ((201 + 88) * escala)}, 16 * escala, 0, WHITE);
    DrawTextEx(fonte.atributoCartas, bufferPopularidade, (Vector2){x + (155 * escala), y + ((201 + 88) * escala)}, 16 * escala, 0, WHITE);
}

void desenharCarta(cartas carta, int x, int y, Molduras molduras, Fonte fonte, float escala, bool isHovered) {

    DrawTextureEx(carta.img, (Vector2){x, y}, 0.0f, escala, WHITE);
    if (carta.supertrunfo == 1) {
        switch (carta.letra) {
        case 'A':

            DrawTextureEx(molduras.azulST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verdeST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amareloST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelhoST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        default:
            break;
        }
    } else {
        switch (carta.letra) {
        case 'A':
            DrawTextureEx(molduras.azul, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verde, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amarelo, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelho, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        default:
            break;
        }
    }
      
    Vector2 posicaoNome = (Vector2){x + (60 * escala), y + (13 * escala)};
    DrawTextEx(fonte.tituloCartas, carta.nome, posicaoNome, 16 * escala, 0, WHITE);
    escreverAtributoCartas(carta, x, y, fonte, escala);

     if (isHovered)
    {
        DrawRectangle(x, y, carta.img.width * escala, carta.img.height * escala, (Color){100, 100, 100, 100});
    }
}


// Function to draw a bigger card on the side
void desenharCartaSelecionada(cartas carta, int x, int y, Molduras molduras, Fonte fonte) {

    float escala = escalaGrande;
    DrawTextureEx(carta.img, (Vector2){x, y}, 0.0f, escala, WHITE);
      if (carta.supertrunfo == 1) {
        switch (carta.letra) {
        case 'A':

            DrawTextureEx(molduras.azulST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verdeST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amareloST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelhoST, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        default:
            break;
        }
    } else {
        switch (carta.letra) {
        case 'A':
            DrawTextureEx(molduras.azul, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'B':
            DrawTextureEx(molduras.verde, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'C':
            DrawTextureEx(molduras.amarelo, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        case 'D':
            DrawTextureEx(molduras.vermelho, (Vector2){x, y}, 0.0f, escala, WHITE);
            break;
        default:
            break;
        }
    }
    Vector2 posicaoNome = (Vector2){x + (60 * escala), y + (13 * escala)};
    DrawTextEx(fonte.tituloCartas, carta.nome, posicaoNome, 16 * escala, 0, WHITE);
    escreverAtributoCartas(carta, x, y, fonte, escala);
}
void desenharTelaDecks(cartas *listaCartas, int quantidadeCartas, Molduras molduras, Fonte fonte, Textura texturas, Estado *estadoAtual)
{
    const int ALTURA = 600;
    const int LARGURA = 800;
    const int larguraCartaPadrao = 155;
    const int alturaCartaPadrao = 248;
    const int larguraCartaReduzida = 115;
    const int alturaCartaReduzida = 183;
    const int espacamentoXPadrao = 23;
    const int espacamentoXReduzido = 18;
    const int espacamentoY = 20;
    const int extremosLateraisPadrao = 54;
    const int extremosLateraisReduzido = 32;

    const int cartasPorLinha = 4;

    int totalLinhas = (quantidadeCartas + cartasPorLinha - 1) / cartasPorLinha; // Arredonda para cima
    int alturaConteudo = totalLinhas * (alturaCartaPadrao + espacamentoY + 20);
    int scrollSpeed = scrollSpeedPadrao;
    
     if (selectedCardIndex != -1) {
          alturaConteudo = totalLinhas * (alturaCartaReduzida + espacamentoY + 20);
          scrollSpeed = scrollSpeedReduzido;
        }

    // Clipping Rectangle - Define the area where cards should be visible
    Rectangle clippingRec = {0, 62, LARGURA, ALTURA - 62}; 
    
    // Control scroll
    if (IsKeyDown(KEY_DOWN))
        offsetY -= scrollSpeed;
    if (IsKeyDown(KEY_UP))
        offsetY += scrollSpeed;
    if (GetMouseWheelMove() != 0)
        offsetY += GetMouseWheelMove() * scrollSpeed;

    // Limitar o scroll
    if (offsetY > 0)
        offsetY = 0;
    if (offsetY < -alturaConteudo + ALTURA - 50)
        offsetY = -alturaConteudo + ALTURA - 50;

    DrawTextureEx(texturas.TexturaFundo, (Vector2){0, 0}, 0.0f, 1.5, WHITE);
    BeginScissorMode(clippingRec.x, clippingRec.y, clippingRec.width, clippingRec.height);
    
    Vector2 mousePos = GetMousePosition();

    // Desenhar cartas
    for (int i = 0; i < quantidadeCartas; i++) {
        int linha = i / cartasPorLinha;
        int coluna = i % cartasPorLinha;

        int posX;
        int posY;
        float escala = escalaPadrao;
        int larguraCarta = larguraCartaPadrao;
        int alturaCarta = alturaCartaPadrao;
        int extremosLaterais = extremosLateraisPadrao;
          int espacamentoX = espacamentoXPadrao;
        
         if (selectedCardIndex != -1) {
            escala = escalaReduzida;
            larguraCarta = larguraCartaReduzida;
            alturaCarta = alturaCartaReduzida;
            extremosLaterais = extremosLateraisReduzido;
             espacamentoX = espacamentoXReduzido;
        }

         if (coluna == 0) {
            posX = extremosLaterais;
        } else {
            posX = extremosLaterais + coluna * (larguraCarta + espacamentoX);
        }
        
        posY = 82 + (linha * (alturaCarta + espacamentoY)) + offsetY;
        

         Rectangle cardRec = (Rectangle){posX, posY, larguraCarta, alturaCarta};
            
            bool isHovered = CheckCollisionPointRec(mousePos, cardRec);
         // Verifique se o estado atual é DECKS antes de permitir a seleção de cartas
        desenharCarta(listaCartas[i], posX, posY, molduras, fonte,escala, isHovered);
        if (isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            selectedCardIndex = i;
        }
    }
        
    EndScissorMode();
    
    // Draw the selected card if the state is DECKS
    if(*estadoAtual == DECKS && selectedCardIndex != -1)
    {
        desenharCartaSelecionada(listaCartas[selectedCardIndex], 564, 80, molduras, fonte);
    }


    DrawRectangle(0, 28, LARGURA, 34, WHITE);
    DrawRectangleLinesEx((Rectangle){0, 28, LARGURA, 34}, 0.8f, (Color){175, 215, 248, 255});
    DrawCircleV((Vector2){46, 45}, 13, WHITE);

        
    if (CheckCollisionPointCircle(mousePos, (Vector2){46, 45}, 13))
    {
        DrawTexture(texturas.setaON, 33, 32, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *estadoAtual = MENU; // Returns to menu.
            offsetY = 0; // Reset scroll offset when exiting deck screen.
            selectedCardIndex = -1; // unselect the card when exiting
        }
    }
    else
    {
        DrawTexture(texturas.setaOFF, 33, 32, WHITE);
    }
    DrawTextEx(fonte.tituloTelas, "Biblioteca de Cartas", (Vector2){70, 32}, 25, 0, BLACK);
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