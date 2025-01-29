#include "raylib.h"
#include "visual.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global variable to store the scroll offset for deck screen
static int offsetY = 0;
// Global variable to store the index of the currently selected card
static int selectedCardIndex = -1;

// Variables for search and filter
static bool showLetterDropdown = false;
static bool showSortByDropdown = false;
static char searchText[64] = "";
static char selectedLetter = '\0';
static int sortByMethod = 0; // 0 = Evolution Chain, 1 = Alphabetical
static bool searchBoxActive = false;
static bool editActive = false;


static float escalaPadrao = 155.37 / 204; // Escala padrão para as cartas na lista.
static float escalaReduzida = 115.0 / 204; // Escala reduzida para cartas não selecionadas
static float escalaGrande = 6800 / 5179;   // escala para carta em destaque
static int scrollSpeedPadrao = 20;        // velocidade do scroll em tamanho padrão
static int scrollSpeedReduzido = 15;      // velocidade do scroll em tamanho reduzido
static double lastCursorBlinkTime;

void inicializarJogo(int largura, int altura, const char *titulo) {
    InitWindow(largura, altura, titulo);
    SetTargetFPS(60);
        srand(time(NULL));
        lastCursorBlinkTime = GetTime();
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

    if (isHovered) {
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

// Function to draw the letter dropdown
void drawLetterDropdown(Rectangle rect, Fonte fonte)
{
    if (showLetterDropdown)
    {
        DrawRectangleRec( rect,WHITE);
        DrawRectangleLinesEx(rect, 0.8f, (Color){175, 215, 248, 255});
        const char *letters[] = {"Todas", "A", "B", "C", "D"};

        for (int i = 0; i < 5; i++)
        {
            Rectangle itemRect = {rect.x, rect.y + i * 30, rect.width, 30};
            Color cor = (Color){13, 35,	55, 255};
            if (selectedLetter == letters[i][0] && i > 0)
                cor = (Color){175, 215, 248, 255};
            else if (selectedLetter == '\0' && i == 0)
                cor = (Color){175, 215, 248, 255};
            DrawTextEx(fonte.atributoCartas, letters[i], (Vector2){itemRect.x + 10, itemRect.y + 5}, 18, 0, cor);
            if (CheckCollisionPointRec(GetMousePosition(), itemRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (i == 0)
                    selectedLetter = '\0';
                else
                    selectedLetter = letters[i][0];
                showLetterDropdown = false;
            }
        }
    }
}

// Function to draw the sort by dropdown
void drawSortByDropdown(Rectangle rect, Fonte fonte)
{
    if (showSortByDropdown)
    {
        DrawRectangleRec( rect,WHITE);
        DrawRectangleLinesEx(rect, 0.8f, (Color){175, 215, 248, 255});
        const char *sortOptions[] = {"Letra da Carta", "Alfabetico"};

        for (int i = 0; i < 2; i++)
        { // Only two sorting options now
            Rectangle itemRect = {rect.x, rect.y + i * 30, rect.width, 30};
            Color cor = (sortByMethod == i) ? (Color){175, 215, 248, 255} : (Color){13, 35,	55, 255};
            DrawTextEx(fonte.atributoCartas, sortOptions[i], (Vector2){itemRect.x + 10, itemRect.y + 5}, 18, 0, cor);
            if (CheckCollisionPointRec(GetMousePosition(), itemRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                sortByMethod = i;
                showSortByDropdown = false;
            }
        }
    }
}

// Function to draw and update the search textbox
void drawSearchBox(Rectangle rect, Fonte fonte, bool isHovered, bool isActive)
{

    DrawRectangleRounded( rect, 0.7f, 0,WHITE);
    DrawRectangleRoundedLinesEx(rect, 0.3f, 0, 0.4f, (Color){175, 215, 248, 255});
    Color textColor = isHovered ? DARKGRAY : BLACK;

    DrawTextEx(fonte.atributoCartas, searchText, (Vector2){rect.x + 5, rect.y + 5}, 18, 0, textColor);

    if (isActive)
    {
        double currentTime = GetTime();
        if ((currentTime - lastCursorBlinkTime) > 0.5)
        {
            DrawLine(rect.x + 5 + MeasureTextEx(fonte.atributoCartas, searchText, 18, 0).x, rect.y + 5, rect.x + 5 + MeasureTextEx(fonte.atributoCartas, searchText, 18, 0).x, rect.y + 21, (Color){13, 35,	55, 255});

            if ((currentTime - lastCursorBlinkTime) > 1.0)
                lastCursorBlinkTime = currentTime;
        }
    }
}

// Function to handle keyboard input for the search box
void updateSearchText()
{
    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (TextLength(searchText) < 63))
        {
            int len = TextLength(searchText);
            searchText[len] = (char)key;
            searchText[len + 1] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        int len = TextLength(searchText);
        if (len > 0)
            searchText[len - 1] = '\0';
    }
}

// Function to filter the cards based on letter, search text and sort the cards
void filterAndSortCards(cartas *listaCartas, int quantidadeCartas, cartas **filteredCards, int *filteredCount) {
    *filteredCount = 0;
    cartas *tempFilteredCards = malloc(sizeof(cartas) * quantidadeCartas);

    for (int i = 0; i < quantidadeCartas; i++) {
        bool includeCard = true;
        if (selectedLetter != '\0' && listaCartas[i].letra != selectedLetter)
            includeCard = false;

        if (TextLength(searchText) > 0 && strstr(listaCartas[i].nome, searchText) == NULL)
            includeCard = false;

        if (includeCard) {
            tempFilteredCards[*filteredCount] = listaCartas[i];
            (*filteredCount)++;
        }
    }

    // Sorting Logic
    if (sortByMethod == 0) { // Sort By evolution chain (currently based on array position)
        // Do not need to sort
    } else if (sortByMethod == 1) { // Alphabetical
        for (int i = 0; i < *filteredCount - 1; i++) {
            for (int j = 0; j < *filteredCount - i - 1; j++) {
                if (strcmp(tempFilteredCards[j].nome, tempFilteredCards[j + 1].nome) > 0) {
                    cartas temp = tempFilteredCards[j];
                    tempFilteredCards[j] = tempFilteredCards[j + 1];
                    tempFilteredCards[j + 1] = temp;
                }
            }
        }
    }

    *filteredCards = tempFilteredCards;
}

void desenharTelaDecks(cartas *listaCartas, int quantidadeCartas, Molduras molduras, Fonte fonte, Textura texturas, Estado *estadoAtual){
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
    const int espacamentoTopo = 27;
    const int alturaSortByDropdown = 60;

    const int cartasPorLinha = 4;

    int totalLinhas = (quantidadeCartas + cartasPorLinha - 1) / cartasPorLinha;
    int alturaConteudo = totalLinhas * (alturaCartaPadrao + espacamentoY + 20);
    int scrollSpeed = scrollSpeedPadrao;

    Vector2 mousePos = GetMousePosition();

    if (selectedCardIndex != -1)
    {
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


    cartas *filteredCards;
    int filteredCount;
    filterAndSortCards(listaCartas, quantidadeCartas, &filteredCards, &filteredCount);

    // Desenhar cartas
    for (int i = 0; i < filteredCount; i++)
    {
        int linha = i / cartasPorLinha;
        int coluna = i % cartasPorLinha;

        int posX;
        int posY;
        float escala = escalaPadrao;
        int larguraCarta = larguraCartaPadrao;
        int alturaCarta = alturaCartaPadrao;
        int extremosLaterais = extremosLateraisPadrao;
        int espacamentoX = espacamentoXPadrao;

        if (selectedCardIndex != -1)
        {
            escala = escalaReduzida;
            larguraCarta = larguraCartaReduzida;
            alturaCarta = alturaCartaReduzida;
            extremosLaterais = extremosLateraisReduzido;
            espacamentoX = espacamentoXReduzido;
        }

        if (coluna == 0)
        {
            posX = extremosLaterais;
        }
        else
        {
            posX = extremosLaterais + coluna * (larguraCarta + espacamentoX);
        }

        posY = 82 + espacamentoTopo + (linha * (alturaCarta + espacamentoY)) + offsetY;

        Rectangle cardRec = (Rectangle){posX, posY, larguraCarta, alturaCarta};

        bool isHovered = CheckCollisionPointRec(mousePos, cardRec);
        desenharCarta(filteredCards[i], posX, posY, molduras, fonte, escala, isHovered);
        if (isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            selectedCardIndex = i;
        }
    }
    EndScissorMode();

    
    DrawRectangle(0, 28, LARGURA, 34, WHITE);
    DrawRectangleLinesEx((Rectangle){0, 28, LARGURA, 34}, 0.8f, (Color){175, 215, 248, 255});
    DrawTextEx(fonte.tituloTelas, "Biblioteca de Cartas", (Vector2){70, 32}, 25, 0, BLACK);

    
    Rectangle letterButtonRec = {250, 32, 80, 24};
    Rectangle sortByButtonRec = {340, 32, 110, 24};
    Rectangle searchBoxRec = {470, 33, 200, 22};
    Rectangle editBoxRec = {700, 33, 22, 22};


    bool letterButtonHovered = CheckCollisionPointRec(mousePos, letterButtonRec);
    bool sortByButtonHovered = CheckCollisionPointRec(mousePos, sortByButtonRec);
    bool searchBoxHovered = CheckCollisionPointRec(mousePos, searchBoxRec);
    bool editBoxHovered = CheckCollisionPointRec(mousePos, editBoxRec);

    if (editActive == 1|| editBoxHovered == 1)
    {
        DrawTextureEx(texturas.editarON,(Vector2){700, 33},0,1,WHITE);
    }else{
        DrawTextureEx(texturas.editarOFF,(Vector2){700, 33},0,1,WHITE);
    }
    if (editBoxHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        editActive = !editActive;
    }
    


    if (searchBoxHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        searchBoxActive = !searchBoxActive;

    if (searchBoxActive)
        updateSearchText();

//(Color){175, 215, 248, 255} : (Color){13, 35,	55, 255};

    DrawRectangleRec(letterButtonRec, letterButtonHovered ? LIGHTGRAY : WHITE);
    DrawRectangleLinesEx(letterButtonRec, 1, (Color){175, 215, 248, 255});
    Color letterColor = letterButtonHovered ? DARKGRAY : (Color){13, 35,	55, 255};
    DrawTextEx(fonte.atributoCartas, "Filtrar", (Vector2){letterButtonRec.x + 5, letterButtonRec.y + 5}, 18, 0, letterColor);

    DrawRectangleRec(sortByButtonRec, sortByButtonHovered ? LIGHTGRAY : WHITE);
    DrawRectangleLinesEx(sortByButtonRec, 1, (Color){175, 215, 248, 255});
    Color sortByColor = sortByButtonHovered ? DARKGRAY : (Color){13, 35,	55, 255};
    DrawTextEx(fonte.atributoCartas, "Ordenar Por", (Vector2){sortByButtonRec.x + 5, sortByButtonRec.y + 5}, 18, 0, sortByColor);

    drawSearchBox(searchBoxRec, fonte, searchBoxHovered, searchBoxActive);

    if (CheckCollisionPointRec(mousePos, letterButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        showLetterDropdown = !showLetterDropdown;
        showSortByDropdown = false; // Close the other dropdown
    }
    if (CheckCollisionPointRec(mousePos, sortByButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        showSortByDropdown = !showSortByDropdown;
        showLetterDropdown = false; // Close the other dropdown
    }

    // Draw the selected card if the state is DECKS
    if (*estadoAtual == DECKS && selectedCardIndex != -1)
    {
        desenharCartaSelecionada(filteredCards[selectedCardIndex], 564, 82 + espacamentoTopo, molduras, fonte);
    }
    drawLetterDropdown((Rectangle){letterButtonRec.x, letterButtonRec.y + 26, letterButtonRec.width, 150}, fonte);
    drawSortByDropdown((Rectangle){sortByButtonRec.x, sortByButtonRec.y + 26, sortByButtonRec.width, alturaSortByDropdown}, fonte);

    DrawCircleV((Vector2){46, 45}, 13, WHITE);

    if (CheckCollisionPointCircle(mousePos, (Vector2){46, 45}, 13))
    {
        DrawTexture(texturas.setaON, 33, 32, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            *estadoAtual = MENU;    // Returns to menu.
            offsetY = 0;            // Reset scroll offset when exiting deck screen.
            selectedCardIndex = -1; // unselect the card when exiting
            searchText[0] = '\0';
            selectedLetter = '\0';
            sortByMethod = 0;
            searchBoxActive = false;
        }
    }
    else
    {
        DrawTexture(texturas.setaOFF, 33, 32, WHITE);
    }
    free(filteredCards);
}

