#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Enum para facilitar manutenção do menu Principal
enum Opcoes
{
    SAIR = 0,
    JOGAR,
    DECKS,
    INSERIR = 1,
    LISTAR,
    PESQUISAR,
    ALTERAR,
    EXCLUIR
};

// Enum para facilitar manutenção do menu Deck

typedef struct
{
    char nome[51];
    char pais[51];
    int supertrunfo; // Agora é booleano
    int anoConstrucao;
    float altura;
    int visitasAnuais;
    int importanciaHistorica;
    int popularidade;
} cartas;

void jogar()
{
    printf("Em breve.\n");
    return;
}

void inserirCartas()
{
    printf("Em breve.\n");
    return;
}

void listarCartas(cartas **deck, int quantidadeCartas)
{
    for (int i = 0; i < quantidadeCartas; i++)
    {
        if ((*deck)[i].supertrunfo == 1)
        {
            printf("%i - %20s| %20s| %5s| %6i| %7.2f| %15i| %4i| %4i\n", i, (*deck)[i].nome, (*deck)[i].pais, "Sim",
                   (*deck)[i].anoConstrucao, (*deck)[i].altura,
                   (*deck)[i].visitasAnuais, (*deck)[i].importanciaHistorica,
                   (*deck)[i].popularidade);
        }
        else if ((*deck)[i].supertrunfo == 0)
        {
            printf("%i - %20s| %20s| %5s| %6i| %7.2f| %15i| %4i| %4i\n", i, (*deck)[i].nome, (*deck)[i].pais, "Nao",
                   (*deck)[i].anoConstrucao, (*deck)[i].altura,
                   (*deck)[i].visitasAnuais, (*deck)[i].importanciaHistorica,
                   (*deck)[i].popularidade);
        }
    }
}

void pesquisarCartas()
{
    printf("Em breve.\n");
    return;
}
void alterarCartas()
{
    printf("Em breve.\n");
    return;
}

void excluirCartas()
{
    printf("Em breve.\n");
    return;
}

void menuDecks(cartas **deck, int quantidadeCartas)
{
    int vmenu = -1;

    do
    {
        printf("O que deseja fazer?\n1 - Inserir cartas no deck\n2 - Listar as cartas do deck\n3 - Pesquisar cartas no deck\n4 - Alterar cartas do deck\n5 - Excluir cartas do deck\n0 - Sair\nDigite a opcao desejada: ");
        scanf("%i", &vmenu);
        switch (vmenu)
        {
        case INSERIR:
            inserirCartas();
            break;
        case LISTAR:
            listarCartas(deck, quantidadeCartas);
            break;
        case PESQUISAR:
            pesquisarCartas();
            break;
        case ALTERAR:
            alterarCartas();
            break;
        case EXCLUIR:
            excluirCartas();
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

void menu(int *vmenu)
{
    printf("O que deseja fazer?\n1 - Jogar\n2 - Decks\n0 - Sair\nDigite a opcao desejada: ");
    scanf("%i", vmenu);
    setbuf(stdin, NULL);
    return;
}

cartas configuracoesIniciais(FILE *arq)
{
    cartas deck;
    fscanf(arq, "%[^,],%[^,],%i,%i,%f,%i,%i,%i\n", deck.nome, deck.pais, &deck.supertrunfo, &deck.anoConstrucao, &deck.altura, &deck.visitasAnuais, &deck.importanciaHistorica, &deck.popularidade);
    if (deck.supertrunfo != 1 && deck.supertrunfo != 0)
    {
        deck.supertrunfo = 0;
    }
    return deck;
}

int contarcartas(FILE *arq)
{
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

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    FILE *arq = fopen("deck.csv", "r");
    if (arq == NULL)
    {
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
            menuDecks(&deck, quantidadeCartas);
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
