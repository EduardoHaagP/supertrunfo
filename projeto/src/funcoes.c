#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

enum Opcoes
{
    SAIR = 0,
    INSERIR,
    LISTAR,
    PESQUISAR,
    ALTERAR,
    EXCLUIR,
};

// Implementação das funções
void jogar() {
    printf("Em breve.\n");
}

void menu(int *vmenu) {
    printf("O que deseja fazer?\n1 - Jogar\n2 - Decks\n0 - Sair\nDigite a opcao desejada: ");
    scanf("%i", vmenu);
    setbuf(stdin, NULL);
}

void menuDecks(cartas **deck, int *quantidadeCartas) {
    int vmenu = -1;

    do
    {
        printf("O que deseja fazer?\n1 - Inserir cartas no deck\n2 - Listar as cartas do deck\n3 - Pesquisar cartas no deck\n4 - Alterar cartas do deck\n5 - Excluir cartas do deck\n0 - Sair\nDigite a opcao desejada: ");
        scanf("%i", &vmenu);
        switch (vmenu)
        {
        case INSERIR:
            inserirCartas(deck, quantidadeCartas);
            break;
        case LISTAR:
            listarCartas(deck, quantidadeCartas);
            break;
        case PESQUISAR:
            pesquisarCartas(deck, quantidadeCartas);
            break;
        case ALTERAR:
            alterarCartas(deck, quantidadeCartas);
            break;
        case EXCLUIR:
            excluirCartas(deck, quantidadeCartas);
            break;
        case SAIR:
            printf("Saindo da Secao decks\n");
            break;
        default:
            printf("O valor digitado nao e valido.\n");
            break;
        }
    } while (vmenu != SAIR);
    return;
}

int contarcartas(FILE *arq) {
    char c;
    int contador = 0; // Inicializa o contador
    int encontrouTexto = 0;

    while ((c = fgetc(arq)) != EOF)
    {
        if (c == '\n') // Contar cada linha completa
        {
            contador++;
            encontrouTexto = 0; // Reinicia o flag de texto encontrado
        }
        else
        {
            encontrouTexto = 1; // Flag de que há conteúdo na linha
        }
    }

    // Adiciona a última linha se houver texto sem '\n'
    if (encontrouTexto)
        contador++;

    return contador;
}

cartas configuracoesIniciais(FILE *arq) {
    cartas deck;
    fscanf(arq, "%[^,],%c,%i,%i,%f,%i,%i,%i\n", deck.nome, &deck.letra, &deck.supertrunfo, &deck.anoConstrucao, &deck.altura, &deck.visitasAnuais, &deck.importanciaHistorica, &deck.popularidade);
    if (deck.supertrunfo != 1 && deck.supertrunfo != 0)
    {
        deck.supertrunfo = 0;
    }
    return deck;
}