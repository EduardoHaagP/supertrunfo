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
static bool delActive = false;
static bool isModalOpen = false;
static bool isPopUPOpen = false;

static float escalaPadrao = 155.37 / 204;  // Escala padrão para as cartas na lista.
static float escalaReduzida = 115.0 / 204; // Escala reduzida para cartas não selecionadas
static float escalaGrande = 6800 / 5179;   // escala para carta em destaque
static int scrollSpeedPadrao = 20;         // velocidade do scroll em tamanho padrão
static int scrollSpeedReduzido = 15;       // velocidade do scroll em tamanho reduzido
static double lastCursorBlinkTime;

void inicializarJogo(int largura, int altura, const char *titulo)
{
    InitWindow(largura, altura, titulo);
    SetTargetFPS(60);
    srand(time(NULL));
    lastCursorBlinkTime = GetTime();
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
    ClearBackground(RAYWHITE);
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

void escreverAtributoCartas(cartas carta, int x, int y, Fonte fonte, float escala, char letra)
{
    Color corNomeAtributo = BLACK;
    Color corValorAtributo = (Color){232, 244, 255, 255};
    switch (letra)
    {
    case 'A':
        corNomeAtributo = (Color){2, 12, 20, 255};
        break;
    case 'B':
        corNomeAtributo = (Color){13, 55, 19, 255};
        break;
    case 'C':
        corNomeAtributo = (Color){152, 107, 1, 255};
        break;
    case 'D':
        corNomeAtributo = (Color){47, 12, 9, 255};
        break;

    default:
        break;
    }
    char bufferAno[20]; // Buffer para armazenar o ano como string
    sprintf(bufferAno, "%d", carta.anoConstrucao);
    DrawTextEx(fonte.atributoCartas, "Ano de Construcao", (Vector2){x + (17 * escala), y + (201 * escala)}, 16 * escala, 0, corNomeAtributo);
    DrawTextEx(fonte.atributoCartas, bufferAno, (Vector2){x + (155 * escala), y + (201 * escala)}, 16 * escala, 0, corValorAtributo);

    char bufferAltura[20]; // Buffer para armazenar o ano como string
    sprintf(bufferAltura, "%d", carta.altura);
    DrawTextEx(fonte.atributoCartas, "Altura", (Vector2){x + (17 * escala), y + ((201 + 22) * escala)}, 16 * escala, 0, corNomeAtributo);
    DrawTextEx(fonte.atributoCartas, bufferAltura, (Vector2){x + (155 * escala), y + ((201 + 22) * escala)}, 16 * escala, 0, corValorAtributo);

    DrawTextEx(fonte.atributoCartas, "Visitas Anuais", (Vector2){x + (17 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, corNomeAtributo);
    if (carta.visitasAnuais > 1000000000) // bilhao
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000000000, " Bi");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, corValorAtributo);
    }
    else if (carta.visitasAnuais > 1000000) // milhao
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000000, " M");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, corValorAtributo);
    }
    else if (carta.visitasAnuais > 1000) // mil
    {
        char resultado[50];
        sprintf(resultado, "%d%s", (carta.visitasAnuais) / 1000, " m");
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, corValorAtributo);
    }
    else
    {
        char resultado[50];
        sprintf(resultado, "%d", (carta.visitasAnuais));
        DrawTextEx(fonte.atributoCartas, resultado, (Vector2){x + (155 * escala), y + ((201 + 44) * escala)}, 16 * escala, 0, corValorAtributo);
    }

    char bufferImpotanciaHistorica[20]; // Buffer para armazenar o ano como string
    sprintf(bufferImpotanciaHistorica, "%d", carta.importanciaHistorica);
    DrawTextEx(fonte.atributoCartas, "Importancia historica", (Vector2){x + (17 * escala), y + ((201 + 66) * escala)}, 16 * escala, 0, corNomeAtributo);
    DrawTextEx(fonte.atributoCartas, bufferImpotanciaHistorica, (Vector2){x + (155 * escala), y + ((201 + 66) * escala)}, 16 * escala, 0, corValorAtributo);

    char bufferPopularidade[20]; // Buffer para armazenar o ano como string
    sprintf(bufferPopularidade, "%d", carta.popularidade);
    DrawTextEx(fonte.atributoCartas, "Popularidade", (Vector2){x + (17 * escala), y + ((201 + 88) * escala)}, 16 * escala, 0, corNomeAtributo);
    DrawTextEx(fonte.atributoCartas, bufferPopularidade, (Vector2){x + (155 * escala), y + ((201 + 88) * escala)}, 16 * escala, 0, corValorAtributo);
}

void desenharCarta(cartas carta, int x, int y, Molduras molduras, Fonte fonte, float escala, bool isHovered)
{
    DrawTextureEx(carta.img, (Vector2){x, y}, 0.0f, escala, WHITE);
    if (carta.supertrunfo == 1)
    {
        switch (carta.letra)
        {
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
    }
    else
    {
        switch (carta.letra)
        {
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
    DrawTextEx(fonte.atributoCartas, carta.nome, posicaoNome, 16 * escala, 0, WHITE);
    escreverAtributoCartas(carta, x, y, fonte, escala, carta.letra);

    if (isHovered)
    {
        Rectangle hover = {x, y, carta.img.width * escala, carta.img.height * escala};
        DrawRectangleRounded(hover, 0.07f, 1, (Color){100, 100, 100, 100});
    }
}

// Function to draw a bigger card on the side
void desenharCartaSelecionada(cartas carta, int x, int y, Molduras molduras, Fonte fonte)
{
    float escala = escalaGrande;
    DrawTextureEx(carta.img, (Vector2){x, y}, 0.0f, escala, WHITE);
    if (carta.supertrunfo == 1)
    {
        switch (carta.letra)
        {
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
    }
    else
    {
        switch (carta.letra)
        {
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
    DrawTextEx(fonte.atributoCartas, carta.nome, posicaoNome, (16 * escala), 0, WHITE);
    escreverAtributoCartas(carta, x, y, fonte, escala, carta.letra);
}

// Function to draw the letter dropdown
void drawLetterDropdown(Rectangle rect, Fonte fonte)
{
    if (showLetterDropdown)
    {
        DrawRectangleRec(rect, WHITE);
        DrawRectangleLinesEx(rect, 0.8f, (Color){175, 215, 248, 255});
        const char *letters[] = {"Todas", "A", "B", "C", "D"};

        for (int i = 0; i < 5; i++)
        {
            Rectangle itemRect = {rect.x, rect.y + i * 30, rect.width, 30};
            Color cor = (Color){13, 35, 55, 255};
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
        DrawRectangleRec(rect, WHITE);
        DrawRectangleLinesEx(rect, 0.8f, (Color){175, 215, 248, 255});
        const char *sortOptions[] = {"Letra da Carta", "Alfabetico"};

        for (int i = 0; i < 2; i++)
        { // Only two sorting options now
            Rectangle itemRect = {rect.x, rect.y + i * 30, rect.width, 30};
            Color cor = (sortByMethod == i) ? (Color){175, 215, 248, 255} : (Color){13, 35, 55, 255};
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

    DrawRectangleRounded(rect, 0.7f, 0, WHITE);
    DrawRectangleRoundedLinesEx(rect, 0.3f, 0, 0.4f, (Color){175, 215, 248, 255});
    Color textColor = isHovered ? DARKGRAY : BLACK;

    DrawTextEx(fonte.atributoCartas, searchText, (Vector2){rect.x + 5, rect.y + 5}, 18, 0, textColor);

    if (isActive)
    {
        double currentTime = GetTime();
        if ((currentTime - lastCursorBlinkTime) > 0.5)
        {
            DrawLine(rect.x + 5 + MeasureTextEx(fonte.atributoCartas, searchText, 18, 0).x, rect.y + 5, rect.x + 5 + MeasureTextEx(fonte.atributoCartas, searchText, 18, 0).x, rect.y + 21, (Color){13, 35, 55, 255});

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
void filterAndSortCards(cartas **listaCartas, int quantidadeCartas, cartas **filteredCards, int *filteredCount)
{
    *filteredCount = 0;
    cartas *tempFilteredCards = malloc(sizeof(cartas) * quantidadeCartas);

    for (int i = 0; i < quantidadeCartas; i++)
    {
        bool includeCard = true;
        if (selectedLetter != '\0' && (*listaCartas)[i].letra != selectedLetter)
            includeCard = false;

        if (TextLength(searchText) > 0 && strstr((*listaCartas)[i].nome, searchText) == NULL)
            includeCard = false;

        if (includeCard)
        {
            tempFilteredCards[*filteredCount] = (*listaCartas)[i];
            (*filteredCount)++;
        }
    }

    // Sorting Logic
    if (sortByMethod == 0)
    { // Sort By evolution chain (currently based on array position)
      // Do not need to sort
    }
    else if (sortByMethod == 1)
    { // Alphabetical
        for (int i = 0; i < *filteredCount - 1; i++)
        {
            for (int j = 0; j < *filteredCount - i - 1; j++)
            {
                if (strcmp(tempFilteredCards[j].nome, tempFilteredCards[j + 1].nome) > 0)
                {
                    cartas temp = tempFilteredCards[j];
                    tempFilteredCards[j] = tempFilteredCards[j + 1];
                    tempFilteredCards[j + 1] = temp;
                }
            }
        }
    }

    *filteredCards = tempFilteredCards;
}

void editCartas(Fonte fonte, Vector2 mousePos, cartas **deck, int quantidadeCartas)
{
    static bool showModal = false;
    static bool dropdownOpen = false;
    static int selectedOption = 0;
    static char inputText[50] = {0};
    static int letterCount = 0;

    // Definições constantes para posicionamento
    const float MODAL_X = 100;
    const float MODAL_Y = 200;
    const float MODAL_WIDTH = 450;
    const float MODAL_HEIGHT = 300;
    const float DROPDOWN_WIDTH = 250;
    const float DROPDOWN_HEIGHT = 30;

    // Definição dos retângulos da interface
    Rectangle modal = {MODAL_X, MODAL_Y, MODAL_WIDTH, MODAL_HEIGHT};
    Rectangle inputTextBox = {MODAL_X + 20, MODAL_Y + 130, DROPDOWN_WIDTH, DROPDOWN_HEIGHT};
    Rectangle dropdownBox = {MODAL_X + 20, MODAL_Y + 165, DROPDOWN_WIDTH, DROPDOWN_HEIGHT};
    Rectangle confirmButton = {MODAL_X + 350, MODAL_Y + 130, 50, 30};
    Rectangle cancelButton = {MODAL_X + 350, MODAL_Y + 170, 50, 30};
    Rectangle closeButton = {MODAL_X + 425, MODAL_Y + 10, 20, 20};

    const char *opcoes[6] = {
        "Nome", "Ano de Construcao", "Altura",
        "Visitas Anuais", "Importancia Historica", "Popularidade"};

    // Atualizar estado com a variável externa
    if (isModalOpen)
    {
        showModal = true;
    }

    // Processamento de entrada e interação
    if (showModal)
    {
        // Fechar modal ao clicar no botão de fechar
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, closeButton))
        {
            showModal = false;
            isModalOpen = false;
            return;
        }

        // Lógica do dropdown
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Verifica se clicou na caixa do dropdown
            if (CheckCollisionPointRec(mousePos, dropdownBox))
            {
                dropdownOpen = !dropdownOpen;
            }
            // Se o dropdown estiver aberto, verifica cliques nas opções
            else if (dropdownOpen)
            {
                for (int i = 0; i < 6; i++)
                {
                    Rectangle optionRect = {
                        dropdownBox.x,
                        dropdownBox.y + DROPDOWN_HEIGHT + (i * DROPDOWN_HEIGHT),
                        DROPDOWN_WIDTH,
                        DROPDOWN_HEIGHT};

                    if (CheckCollisionPointRec(mousePos, optionRect))
                    {
                        selectedOption = i;
                        dropdownOpen = false;
                        break;
                    }
                }
            }
            // Se clicou fora do dropdown quando ele está aberto, fecha
            else if (!CheckCollisionPointRec(mousePos, dropdownBox))
            {
                dropdownOpen = false;
            }
        }

        // Processamento de entrada de texto
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < 49))
            {
                inputText[letterCount] = (char)key;
                inputText[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            inputText[letterCount] = '\0';
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Processamento dos botões de confirmação e cancelamento
            if (CheckCollisionPointRec(mousePos, confirmButton))
            {
                if (selectedCardIndex >= 0)
                {
                    switch (selectedOption)
                    {
                    case 0:
                        strcpy((*deck)[selectedCardIndex].nome, inputText);
                        break;
                    case 1:
                        (*deck)[selectedCardIndex].anoConstrucao = atoi(inputText);
                        break;
                    case 2:
                        (*deck)[selectedCardIndex].altura = atoi(inputText);
                        break;
                    case 3:
                        (*deck)[selectedCardIndex].visitasAnuais = atoi(inputText);
                        break;
                    case 4:
                        (*deck)[selectedCardIndex].importanciaHistorica = atoi(inputText);
                        break;
                    case 5:
                        (*deck)[selectedCardIndex].popularidade = atoi(inputText);
                        break;
                    }
                }

                showModal = false;
                isModalOpen = false;
                inputText[0] = '\0';
                letterCount = 0;
                salvarNoCSV(deck, quantidadeCartas); // Chamada corrigida
            }
            // Cancelar edição
            else if (CheckCollisionPointRec(mousePos, cancelButton))
            {
                showModal = false;
                isModalOpen = false;
                inputText[0] = '\0';
                letterCount = 0;
            }
        }
    }

    // Renderização
    if (showModal)
    {
        // Background escuro
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 150});

        // Modal
        DrawRectangleRounded(modal, 0.07f, 0, WHITE);
        DrawRectangleRoundedLinesEx(modal, 0.07f, 0, 0.4f, (Color){175, 215, 248, 255});

        // Título do modal
        char bufferText[100];
        sprintf(bufferText, "Editar %s", (*deck)[selectedCardIndex].nome);
        DrawTextEx(fonte.tituloTelas, bufferText,
                   (Vector2){MODAL_X + 40, MODAL_Y + 10}, 20, 0, BLACK);

        // Botão de fechar
        DrawRectangleRec(closeButton, RED);
        if (CheckCollisionPointRec(mousePos, closeButton))
        {
            DrawRectangleRec(closeButton, (Color){125, 14, 14, 255});
        }
        DrawTextEx(fonte.atributoCartas, "X",
                   (Vector2){closeButton.x + 5, closeButton.y - 2}, 20, 0, WHITE);

        // Caixa de entrada de texto
        DrawRectangleRec(inputTextBox, WHITE);
        DrawTextEx(fonte.atributoCartas, inputText,
                   (Vector2){inputTextBox.x + 5, inputTextBox.y + 5}, 20, 0, BLACK);
        DrawRectangleLinesEx(inputTextBox, 1, BLACK);

        // Dropdown
        DrawRectangleRec(dropdownBox, WHITE);
        DrawTextEx(fonte.atributoCartas, opcoes[selectedOption],
                   (Vector2){dropdownBox.x + 5, dropdownBox.y + 5}, 20, 0, BLACK);
        DrawRectangleLinesEx(dropdownBox, 1, BLACK);

        // Opções do dropdown quando aberto
        if (dropdownOpen)
        {
            for (int i = 0; i < 6; i++)
            {
                Rectangle optionRect = {
                    dropdownBox.x,
                    dropdownBox.y + DROPDOWN_HEIGHT + (i * DROPDOWN_HEIGHT),
                    DROPDOWN_WIDTH,
                    DROPDOWN_HEIGHT};

                // Highlight da opção sob o mouse
                Color bgColor = CheckCollisionPointRec(mousePos, optionRect) ? LIGHTGRAY : WHITE;

                DrawRectangleRec(optionRect, bgColor);
                DrawTextEx(fonte.atributoCartas, opcoes[i],
                           (Vector2){optionRect.x + 5, optionRect.y + 5}, 20, 0, BLACK);
                DrawRectangleLinesEx(optionRect, 1, BLACK);
            }
        }

        // Botões de confirmação e cancelamento
        // Confirm button
        DrawRectangleRec(confirmButton, GREEN);
        if (CheckCollisionPointRec(mousePos, confirmButton))
        {
            DrawRectangleRec(confirmButton, DARKGREEN);
        }
        DrawTextEx(fonte.atributoCartas, "Ok",
                   (Vector2){confirmButton.x + 15, confirmButton.y + 5}, 20, 0, WHITE);

        // Cancel button
        DrawRectangleRec(cancelButton, RED);
        if (CheckCollisionPointRec(mousePos, cancelButton))
        {
            DrawRectangleRec(cancelButton, MAROON);
        }
        DrawTextEx(fonte.atributoCartas, "X",
                   (Vector2){cancelButton.x + 20, cancelButton.y + 5}, 20, 0, WHITE);
    }

    // Atualizar variável externa
    isModalOpen = showModal;
}

void delCartas(Fonte fonte, Vector2 mousePos, cartas **deck, int *quantidadeCartas)
{
    static bool showPopUP = false;

    const float POPUP_X = 240;
    const float POPUP_Y = 220;
    const float POPUP_WIDTH = 280;
    const float POPUP_HEIGHT = 160;

    Rectangle delPopUP = {POPUP_X, POPUP_Y, POPUP_WIDTH, POPUP_HEIGHT};
    Rectangle confirmButton = {258, 337, 244, 23};
    Rectangle cancelDelButton = {258, 337, 113, 23};
    Rectangle confirmDelButton = {389, 337, 113, 23};

    if (isPopUPOpen)
    {
        showPopUP = true;
    }
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 150});

    if (showPopUP)
    {
        DrawRectangleRounded(delPopUP, 0.03f, 1, WHITE);

        if ((*quantidadeCartas) <= 32)
        {
            DrawTextEx(fonte.tituloTelas, "Nao e possavel deletar cartas", (Vector2){298, 280}, 18, 0, (Color){93, 128, 156, 255});
            DrawTextEx(fonte.atributoCartas, "O jogo nao permite uma quantidade menor que 32", (Vector2){258, 303}, 14, 0, (Color){93, 128, 156, 255 * 0.9});
            DrawTextEx(fonte.atributoCartas, "cartas", (Vector2){366, 311}, 14, 0, (Color){93, 128, 156, 255 * 0.9});

            DrawRectangleRounded(confirmButton, 0.03f, 1, (Color){93, 128, 156, 255});
            DrawTextEx(fonte.tituloTelas, "Confirmar", (Vector2){352, 340}, 20, 0, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, confirmButton))
            {
                showPopUP = false; // Fecha o modal
            }
        }
        else
        {
            DrawTextEx(fonte.tituloTelas, "Tem certeza que deseja excluir essa carta?", (Vector2){258, 280}, 18, 0, (Color){93, 128, 156, 255});
            DrawTextEx(fonte.atributoCartas, "Ao excluir essa carta vc tem a chance de alterar a", (Vector2){258, 300}, 14, 0, (Color){93, 128, 156, 255 * 0.9});
            DrawTextEx(fonte.atributoCartas, "identidade do jogo e ao excluir ela nao ha volta", (Vector2){267, 314}, 14, 0, (Color){93, 128, 156, 255 * 0.9});

            DrawRectangleRounded(cancelDelButton, 0.1f, 1, WHITE);
            DrawRectangleRoundedLines(cancelDelButton, 0.1f, 1,
                                      CheckCollisionPointRec(mousePos, cancelDelButton) ? (Color){13, 35, 55, 255} : (Color){93, 128, 156, 255});
            DrawTextEx(fonte.tituloTelas, "Cancelar", (Vector2){264, 340}, 20, 0, WHITE);

            CheckCollisionPointRec(mousePos, confirmDelButton)
                ? DrawRectangleRounded(confirmDelButton, 0.1f, 1, (Color){13, 35, 55, 255})
                : DrawRectangleRounded(confirmDelButton, 0.1f, 1, (Color){93, 128, 156, 255});
            DrawTextEx(fonte.tituloTelas, "Confirmar", (Vector2){394, 340}, 20, 0, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, confirmDelButton))
            {
                if (selectedCardIndex < 0 || selectedCardIndex >= *quantidadeCartas)
                {
                    return;
                }

                // Liberar a textura da carta removida
                UnloadTexture((*deck)[selectedCardIndex].img);

                // Deslocar elementos no array para remover a carta
                for (int i = selectedCardIndex; i < (*quantidadeCartas) - 1; i++)
                {
                    (*deck)[i] = (*deck)[i + 1];
                }

                (*quantidadeCartas)--;

                // Realocar memória para o novo tamanho
                cartas *temp = (cartas *)realloc(*deck, (*quantidadeCartas) * sizeof(cartas));
                if (temp != NULL)
                {
                    *deck = temp;
                }

                // Garantir que ainda haja um Super Trunfo no deck
                bool temSuperTrunfo = false;
                for (int i = 0; i < *quantidadeCartas; i++)
                {
                    if ((*deck)[i].supertrunfo == 1)
                    {
                        temSuperTrunfo = true;
                        break;
                    }
                }
                if (!temSuperTrunfo && *quantidadeCartas > 0)
                {
                    (*deck)[0].supertrunfo = 1;
                }

                salvarNoCSV(deck, (*quantidadeCartas));
                selectedCardIndex = -1;
                showPopUP = false;
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, cancelDelButton))
            {
                showPopUP = false;
            }
        }
    }

    isPopUPOpen = showPopUP;
}

void desenharTelaDecks(cartas *listaCartas[], int *quantidadeCartas, Molduras molduras, Fonte fonte, Textura texturas, Estado *estadoAtual)
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
    const int espacamentoTopo = 27;
    const int alturaSortByDropdown = 60;

    const int cartasPorLinha = 4;

    int totalLinhas = ((*quantidadeCartas) + cartasPorLinha - 1) / cartasPorLinha;
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
    DrawRectangle(0, 28, LARGURA, 34, WHITE);
    DrawRectangleLinesEx((Rectangle){0, 28, LARGURA, 34}, 0.8f, (Color){175, 215, 248, 255});
    DrawTextEx(fonte.atributoCartas, "Biblioteca de Cartas", (Vector2){70, 32}, 25, 0, BLACK);

    Rectangle editBoxRec = {700, 33, 22, 22};
    bool editBoxHovered = CheckCollisionPointRec(mousePos, editBoxRec);
    if ((editActive && selectedCardIndex != -1) || (editBoxHovered && selectedCardIndex != -1 && !isModalOpen))
    {
        DrawTextureEx(texturas.editarON, (Vector2){700, 33}, 0, 1, WHITE);

        if (editBoxHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedCardIndex != -1 && !isModalOpen)
        {
            editActive = !editActive;
            if (editActive)
            {
                isModalOpen = true;
            }
        }
    }
    else if (selectedCardIndex != -1)
    {
        DrawTextureEx(texturas.editarOFF, (Vector2){700, 33}, 0, 1, WHITE);
    }

    BeginScissorMode(clippingRec.x, clippingRec.y, clippingRec.width, clippingRec.height);

    cartas *filteredCards;
    int filteredCount;
    filterAndSortCards(listaCartas, (*quantidadeCartas), &filteredCards, &filteredCount);

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
        bool isHovered = false;
        if (isModalOpen == 0 && isPopUPOpen == 0)
        {
            isHovered = CheckCollisionPointRec(mousePos, cardRec);
        }
        desenharCarta(filteredCards[i], posX, posY, molduras, fonte, escala, isHovered);

        if (isModalOpen == 0 && isPopUPOpen == 0)
        {
            if (isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                selectedCardIndex = i;
            }
        }
    }
    EndScissorMode();

    Rectangle letterButtonRec = {250, 32, 80, 24};
    Rectangle sortByButtonRec = {340, 32, 110, 24};
    Rectangle searchBoxRec = {470, 33, 200, 22};

    bool letterButtonHovered = CheckCollisionPointRec(mousePos, letterButtonRec);
    bool sortByButtonHovered = CheckCollisionPointRec(mousePos, sortByButtonRec);
    bool searchBoxHovered = CheckCollisionPointRec(mousePos, searchBoxRec);

    if (searchBoxHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        searchBoxActive = !searchBoxActive;

    if (searchBoxActive)
        updateSearchText();

    DrawRectangleRec(letterButtonRec, letterButtonHovered ? LIGHTGRAY : WHITE);
    DrawRectangleLinesEx(letterButtonRec, 1, (Color){175, 215, 248, 255});
    Color letterColor = letterButtonHovered ? DARKGRAY : (Color){13, 35, 55, 255};
    DrawTextEx(fonte.atributoCartas, "Filtrar", (Vector2){letterButtonRec.x + 5, letterButtonRec.y + 5}, 18, 0, letterColor);

    DrawRectangleRec(sortByButtonRec, sortByButtonHovered ? LIGHTGRAY : WHITE);
    DrawRectangleLinesEx(sortByButtonRec, 1, (Color){175, 215, 248, 255});
    Color sortByColor = sortByButtonHovered ? DARKGRAY : (Color){13, 35, 55, 255};
    DrawTextEx(fonte.atributoCartas, "Ordenar Por", (Vector2){sortByButtonRec.x + 5, sortByButtonRec.y + 5}, 18, 0, sortByColor);

    drawSearchBox(searchBoxRec, fonte, searchBoxHovered, searchBoxActive);

    if (!isModalOpen)
    {
        if (CheckCollisionPointRec(mousePos, letterButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            showLetterDropdown = !showLetterDropdown;
            showSortByDropdown = false; // Close the other dropdown
        }
    }
    if (!isModalOpen)
    {
        if (CheckCollisionPointRec(mousePos, sortByButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            showSortByDropdown = !showSortByDropdown;
            showLetterDropdown = false; // Close the other dropdown
        }
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
        if (!isModalOpen)
        {
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
    }
    else
    {
        DrawTexture(texturas.setaOFF, 33, 32, WHITE);
    }
    Rectangle delBoxRec = {760, 33, 22, 22};
    bool delBoxHovered = CheckCollisionPointRec(mousePos, delBoxRec);
    if ((isPopUPOpen && selectedCardIndex != -1) || (delBoxHovered && selectedCardIndex != -1 && !isPopUPOpen))
    {
        DrawTextureEx(texturas.trash, (Vector2){760, 33}, 0, 20, WHITE);

        if (delBoxHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedCardIndex != -1 && !isPopUPOpen)
        {
            delActive = !delActive;
            if (delActive)
            {
                isPopUPOpen = true;
            }
        }
    }
    else if (selectedCardIndex != -1)
    {
        DrawTextureEx(texturas.trash, (Vector2){760, 33}, 0, 20, WHITE);
    }

    if (selectedCardIndex >= 0)
    {
        if (editActive)
            editCartas(fonte, mousePos, listaCartas, (*quantidadeCartas));
        if (delActive)
        {
            delCartas(fonte, mousePos, listaCartas, quantidadeCartas);
        }
        if (!isModalOpen)
            editActive = false;
        if (!isPopUPOpen)
        {
            delActive = false;
        }
    }
    free(filteredCards);
}
