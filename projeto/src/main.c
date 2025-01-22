#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"
#include "raylib.h"

enum Opcoes
{
    SAIR = 0,
    JOGAR,
    DECKS,
};


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello World Raylib 5.5");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loop principal do jogo
    while (!WindowShouldClose())    // Detecta o botão de fechar a janela ou a tecla ESC
    {
        // Atualizar
        //----------------------------------------------------------------------------------
        // TODO: Atualize suas variáveis aqui
        //----------------------------------------------------------------------------------

        // Desenha
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
 
            DrawText("Parabéns! Você criou sua primeiro programa com Raylib!", 120, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Desinicialização
    //--------------------------------------------------------------------------------------
    CloseWindow();



    FILE *arq = fopen("deck.csv", "r");
    if (arq == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    int quantidadeCartas = contarcartas(arq);
    rewind(arq);

    cartas *deck = (cartas *)malloc(quantidadeCartas * sizeof(cartas));
    if (deck == NULL)
    {
        printf("Erro ao alocar memoria\n");
        fclose(arq);
        exit(1);
    }

    for (int i = 0; i < quantidadeCartas; i++)
    {
        deck[i] = configuracoesIniciais(arq);
    }

    fclose(arq);

    int vmenu = -1;
    do
    {
        menu(&vmenu);
        switch (vmenu)
        {
        case JOGAR:
            jogar();
            break;
        case DECKS:
            menuDecks(&deck, &quantidadeCartas);
            break;
        case SAIR:
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("O valor digitado nao e valido.\n");
            break;
        }
    } while (vmenu != SAIR);

    free(deck);
    return 0;
}