#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes.h"

enum Opcoes
{
    SAIR = 0,
    JOGAR,
    DECKS,
};


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

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