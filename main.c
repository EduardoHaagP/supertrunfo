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

void inserirCartas(cartas **deck, int *quantidadeCartas)
{
    int maisUmaCarta = 0;
    printf("Voce deseja adicionar uma carta?\n1 - Sim\n0 - Nao\nDigite aqui: ");
    scanf("%i", &maisUmaCarta);
    setbuf(stdin, NULL);

    while (maisUmaCarta != 0 && maisUmaCarta != 1)
    {
        printf("Valor invalido!\nDigite novamente: ");
        scanf("%i", &maisUmaCarta);
        setbuf(stdin, NULL);
    }
    
    FILE *arq = NULL;

    if (maisUmaCarta == 1) {
          arq = fopen("deck.csv", "w"); // Abre para escrita no inicio da função.
        if (arq == NULL)
        {
            printf("Erro na abertura do arquivo\n");
            exit(1);
        }
    }

    while (maisUmaCarta == 1)
    {
        cartas carta;

        printf("Qual o nome do monumento que deseja adicionar: ");
        fgets(carta.nome, sizeof(carta.nome), stdin);
        carta.nome[strcspn(carta.nome, "\n")] = '\0';

        printf("Em qual pais esse monumento esta localizado: ");
        fgets(carta.pais, sizeof(carta.pais), stdin);
        carta.pais[strcspn(carta.pais, "\n")] = '\0';

        int resposta;
        printf("Deseja que ele se torne o super trunfo\n1 - sim\n0 - nao\nDigite aqui: ");
        scanf("%i", &resposta);
        setbuf(stdin, NULL);
        while (resposta != 1 && resposta != 0)
        {
            printf("Resposta invalida!\nDigite novamente: ");
            scanf("%i", &resposta);
            setbuf(stdin, NULL);
        }

        if (resposta == 1)
        {
            // Desmarca todos os super trunfos no deck
            for (int i = 0; i < (*quantidadeCartas); i++)
            {
                (*deck)[i].supertrunfo = 0;
            }
            carta.supertrunfo = 1;
        }
        else
        {
            carta.supertrunfo = 0;
        }

        printf("Em que ano ele terminou de ser construido (em caso de ser antes de cristo digite o valor negativo): ");
        scanf("%i", &carta.anoConstrucao);
        setbuf(stdin, NULL);

        printf("Qual a altura desse monumento: ");
        scanf("%f", &carta.altura);
        setbuf(stdin, NULL);

        printf("Quantas visitas anuais esse monumento recebe em media: ");
        scanf("%i", &carta.visitasAnuais);
        setbuf(stdin, NULL);

        printf("De 0 a 10 qual a sua importancia historica: ");
        scanf("%i", &resposta);
        setbuf(stdin, NULL);
        while (resposta > 10 || resposta < 0)
        {
            printf("Resposta invalida!\nDigite novamente: ");
            scanf("%i", &resposta);
            setbuf(stdin, NULL);
        }
        carta.importanciaHistorica = resposta;

        printf("De 0 a 10 qual a sua popularidade: ");
        scanf("%i", &resposta);
        setbuf(stdin, NULL);
        while (resposta > 10 || resposta < 0)
        {
            printf("Resposta invalida!\nDigite novamente: ");
            scanf("%i", &resposta);
            setbuf(stdin, NULL);
        }
        carta.popularidade = resposta;

        *deck = realloc(*deck, (*quantidadeCartas + 1) * sizeof(cartas));
        if (*deck == NULL)
        {
            printf("Erro: Memória insuficiente!\n");
            if(arq != NULL)
            {
                fclose(arq);
            }
            exit(1);
        }
        (*deck)[*quantidadeCartas] = carta;
        (*quantidadeCartas)++;

        printf("Voce deseja adicionar mais uma carta?\n1 - Sim\n0 - Nao\nDigite aqui: ");
        scanf("%i", &maisUmaCarta);
        setbuf(stdin, NULL);
        while (maisUmaCarta != 0 && maisUmaCarta != 1)
        {
            printf("Valor invalido!\nDigite novamente: ");
            scanf("%i", &maisUmaCarta);
            setbuf(stdin, NULL);
        }
    }
    if (arq != NULL) {
        for (int i = 0; i < (*quantidadeCartas); i++) {
             fprintf(arq, "%s,%s,%i,%i,%.2f,%i,%i,%i\n", (*deck)[i].nome, (*deck)[i].pais, (*deck)[i].supertrunfo,
                     (*deck)[i].anoConstrucao, (*deck)[i].altura, (*deck)[i].visitasAnuais, (*deck)[i].importanciaHistorica,
                     (*deck)[i].popularidade);
         }
         fclose(arq);
    }
}

void listarCartas(cartas **deck, int *quantidadeCartas)
{
    for (int i = 0; i < (*quantidadeCartas); i++)
    {
        if ((*deck)[i].supertrunfo == 1)
        {
            printf("%i - %35s| %20s| %5s| %6i| %7.2f| %15i| %4i| %4i\n", i, (*deck)[i].nome, (*deck)[i].pais, "Sim",
                   (*deck)[i].anoConstrucao, (*deck)[i].altura,
                   (*deck)[i].visitasAnuais, (*deck)[i].importanciaHistorica,
                   (*deck)[i].popularidade);
        }
        else if ((*deck)[i].supertrunfo == 0)
        {
            printf("%i - %35s| %20s| %5s| %6i| %7.2f| %15i| %4i| %4i\n", i, (*deck)[i].nome, (*deck)[i].pais, "Nao",
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

void menuDecks(cartas **deck, int *quantidadeCartas)
{
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
