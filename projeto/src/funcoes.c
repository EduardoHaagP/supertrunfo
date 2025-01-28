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

    // Lê o arquivo caractere por caractere
    while ((c = fgetc(arq)) != EOF) {
        if (c == '\n') { // Contar cada linha completa
            if (encontrouTexto) { // Se houve texto na linha, conta a linha
                contador++;
            }
            encontrouTexto = 0; // Reinicia o flag de texto encontrado
        } else {
            encontrouTexto = 1; // Flag de que há conteúdo na linha
        }
    }

    // Se a última linha não terminar com '\n' e tiver texto, conta essa linha
    if (encontrouTexto) {
        contador++;
    }

    return contador;
}

cartas *carregarDeck(const char *nomeArquivo, int *quantidadeCartas) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro na abertura do arquivo\n");
        exit(1);
    }

    *quantidadeCartas = contarcartas(arq);
    rewind(arq);

    cartas *deck = (cartas *)malloc((*quantidadeCartas) * sizeof(cartas));
    if (deck == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arq);
        exit(1);
    }

    for (int i = 0; i < *quantidadeCartas; i++) {
        deck[i] = configuracoesIniciais(arq);
    }

    fclose(arq);
    return deck;
}

cartas configuracoesIniciais(FILE *arq) {
    cartas deck;
    // Certifique-se de que está lendo apenas 8 campos
    fscanf(arq, "%[^,],%c,%i,%i,%i,%i,%i,%i,%[^\n]\n", deck.nome, &deck.letra, &deck.supertrunfo, 
                                                &deck.anoConstrucao, &deck.altura, 
                                                &deck.visitasAnuais, &deck.importanciaHistorica, 
                                                &deck.popularidade,deck.arqimg);
    // Verificar se a leitura foi bem-sucedida
    if (deck.supertrunfo != 1 && deck.supertrunfo != 0) {
        deck.supertrunfo = 0;
    }
    return deck;
}

