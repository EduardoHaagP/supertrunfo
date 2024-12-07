#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h> // Biblioteca para bool

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
    bool supertrunfo; // Agora é booleano
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

void listarCartas()
{
    printf("Em breve.\n");
    return;
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


void menuDecks(int *vmenu)
{
    printf("O que deseja fazer?\n1 - Inserir cartas no deck\n2 - Listar as cartas do deck\n3 - Pesquisar cartas no deck\n4 - Alterar cartas do deck\n5 - Excluir cartas do deck\n0 - Sair\nDigite a opção desejada: ");
    scanf("%i", vmenu);
    return;
}

void decks()
{
    int vmenud = -1;
    do
    {
        menuDecks(&vmenud);
        switch (vmenud)
        {
        case INSERIR:
            inserirCartas();
            break;
        case LISTAR:
            listarCartas();
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
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("O valor digitado não é válido\n");
            break;
        }
    } while (vmenud != SAIR);
    return;
}

void menu(int *vmenu)
{
    printf("O que deseja fazer?\n1 - Jogar\n2 - Decks\n0 - Sair\nDigite a opção desejada: ");
    if (scanf("%i", vmenu) != 1)
    {
        printf("Entrada inválida! Digite novamente.\n");
        while (getchar() != '\n')
            ; // Limpa o buffer do teclado
        *vmenu = -1;
    }
    return;
}

cartas configuracoesIniciais(FILE *arq)
{
    cartas deck;
    char linha[256]; // Buffer para a linha
    if (fgets(linha, sizeof(linha), arq) != NULL)
    {
        // Usando strtok para dividir os campos com base na vírgula
        char *token = strtok(linha, ",");
        strncpy(deck.nome, token, sizeof(deck.nome));

        token = strtok(NULL, ",");
        strncpy(deck.pais, token, sizeof(deck.pais));

        token = strtok(NULL, ",");
        deck.supertrunfo = (atoi(token) != 0); // Converte para bool

        token = strtok(NULL, ",");
        deck.anoConstrucao = atoi(token);

        token = strtok(NULL, ",");
        deck.altura = atof(token);

        token = strtok(NULL, ",");
        deck.visitasAnuais = atoi(token);

        token = strtok(NULL, ",");
        deck.importanciaHistorica = atoi(token);

        token = strtok(NULL, ",");
        deck.popularidade = atoi(token);
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
        printf("Erro ao alocar memória\n");
        fclose(arq);
        exit(1);
    }

    for (int i = 0; i < quantidadeCartas; i++)
    {
        deck[i] = configuracoesIniciais(arq);
        printf("%s, %s, %s, %i, %.2f, %i, %i, %i\n",
               deck[i].nome, deck[i].pais,
               deck[i].supertrunfo ? "Sim" : "Nao",
               deck[i].anoConstrucao, deck[i].altura,
               deck[i].visitasAnuais, deck[i].importanciaHistorica,
               deck[i].popularidade);
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
            decks();
            break;
        case SAIR:
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("O valor digitado não é válido.\n");
            break;
        }
    } while (vmenu != SAIR);

    free(deck);

    return 0;
}
