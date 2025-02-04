#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartas.h"

enum Opcoes
{
    NOME = 1,
    LETRA,
    SUPERTRUNFO,
    ANOCONSTRUCAO,
    ALTURA,
    VISITASANUAIS,
    IMPORTANCIAHISTORICA,
    POPULARIDADE
};

void inserirCartas(cartas **deck, cartas cartaNova,int *quantidadeCartas) {
    FILE *arq = NULL;


        arq = fopen("deck.csv", "w");
        if (arq == NULL)
        {
            printf("Erro na abertura do arquivo\n");
            exit(1);
        }
        if (cartaNova.supertrunfo == 1)
        {
            for (int i = 0; i < (*quantidadeCartas); i++)
            {
                (*deck)[i].supertrunfo = 0;
            }
            
        }
        


        *deck = realloc(*deck, (*quantidadeCartas + 1) * sizeof(cartas));
        if (*deck == NULL)
        {
            printf("Erro: Memória insuficiente!\n");
            if (arq != NULL)
            {
                fclose(arq);
            }
            exit(1);
        }
        (*deck)[*quantidadeCartas] = cartaNova;
        (*quantidadeCartas)++;
    
    salvarNoCSV(deck, (*quantidadeCartas));
    return;
}
    
void alterarCartas(cartas **deck, int *quantidadeCartas) {
    int indice;
    int quantidadeCartasAux = *quantidadeCartas - 1;
    printf("Qual o Indice da carta que voce deseja alterar (0 - %i): ", quantidadeCartasAux);
    scanf("%i", &indice);
    setbuf(stdin, NULL);
    while (indice > quantidadeCartasAux || indice < 0)
    {
        printf("O indice digitado nao corresponde a nenhuma carta!\n Digite novamente: ");
        scanf("%i", &indice);
        setbuf(stdin, NULL);
    }
    printf("%6s - %35s| %7s| %14s| %16s| %12s| %15s| %22s| %14s\n", "Indice", "Nome do Monumento", "Letra", "Super Trunfo", "Ano Construcao", "Altura", "Visitas Anuais", "Importancia Historica", "Popularidade");
    if ((*deck)[indice].supertrunfo == 1)
    {
        printf("%6i - %35s| %7c| %14s| %16i| %12i| %15i| %22i| %14i\n", indice, (*deck)[indice].nome, (*deck)[indice].letra, "Sim",
               (*deck)[indice].anoConstrucao, (*deck)[indice].altura,
               (*deck)[indice].visitasAnuais, (*deck)[indice].importanciaHistorica,
               (*deck)[indice].popularidade);
    }
    else if ((*deck)[indice].supertrunfo == 0)
    {
        printf("%6i - %35s| %7c| %14s| %16i| %12i| %15i| %22i| %14i\n", indice, (*deck)[indice].nome, (*deck)[indice].letra, "Nao",
               (*deck)[indice].anoConstrucao, (*deck)[indice].altura,
               (*deck)[indice].visitasAnuais, (*deck)[indice].importanciaHistorica,
               (*deck)[indice].popularidade);
    }
    int resposta;
    printf("E essa carta que voce deseja alterar?\n1-Sim\n2-nao\nDigite aqui: ");
    scanf("%i", &resposta);
    setbuf(stdin, NULL);
    while (resposta != 1 && resposta != 0)
    {
        printf("Resposta invalida\nDigite novamente: ");
        scanf("%i", &resposta);
        setbuf(stdin, NULL);
    }
    if (resposta == 0)
    {
        alterarCartas(deck, quantidadeCartas);
    }
    else
    {
        int respostaAlterarcarta = -1;
        printf("O que deseja alterar nessa carta\n1-Nome\n2-Letra\n3-Super trunfo\n4-Ano Construcao\n5- Altura\n6-Visitas Anuais\n7-Importancia Historica\n8-Popularidade\nDigite aqui: ");
        scanf("%i", &respostaAlterarcarta);
        setbuf(stdin, NULL);
        while (respostaAlterarcarta > 8 || respostaAlterarcarta < 1)
        {
            printf("Resposta invalida\nDigite novamente: ");
            scanf("%i", &respostaAlterarcarta);
        }
        int respostasAux;
        switch (respostaAlterarcarta)
        {
        case NOME:
            printf("Qual o nome que deseja atribuir a essa carta: ");
            fgets((*deck)[indice].nome, sizeof((*deck)[indice]), stdin);
            (*deck)[indice].nome[strcspn((*deck)[indice].nome, "\n")] = '\0';
            setbuf(stdin, NULL);
            break;
        case LETRA:
            printf("Qual letra voce deseja que essa carta possua:1 - A\n2 - B\n3 - C\n4 - D\nDigite aqui: ");
            scanf("%i", &respostasAux);
            setbuf(stdin, NULL);
            if (respostasAux == 1)
            {
                (*deck)[indice].letra = 'A';
            }
            else if (respostasAux == 2)
            {
                (*deck)[indice].letra = 'B';
            }
            else if (respostasAux == 3)
            {
                (*deck)[indice].letra = 'C';
            }
            else if (respostasAux == 4)
            {
                (*deck)[indice].letra = 'D';
            }
            break;
        case SUPERTRUNFO:
            printf("Deseja que ele se torne o super trunfo\n(Somente pode existir 1 Super Trunfo! Caso escolha sim o outro existente deixara de ser)\n1 - sim\n0 - nao\nDigite aqui: ");
            scanf("%i", &respostasAux);
            setbuf(stdin, NULL);
            while (respostasAux != 1 && respostasAux != 0)
            {
                printf("Resposta invalida!\nDigite novamente: ");
                scanf("%i", &respostasAux);
                setbuf(stdin, NULL);
            }

            if (respostasAux == 1)
            {
                // Desmarca todos os super trunfos no deck
                for (int i = 0; i < (*quantidadeCartas); i++)
                {
                    (*deck)[i].supertrunfo = 0;
                }
                (*deck)[indice].supertrunfo = 1;
            }
            else
            {
                (*deck)[indice].supertrunfo = 0;
            }
            break;
        case ANOCONSTRUCAO:
            printf("Qual o ano de termino da construcao deseja atribuir a essa carta (em caso de ser antes de cristo digite o valor negativo): ");
            scanf("%i", &(*deck)[indice].anoConstrucao);
            setbuf(stdin, NULL);

            break;
        case ALTURA:
            printf("Qual a altura desse monumento: ");
            scanf("%i", &(*deck)[indice].altura);
            setbuf(stdin, NULL);
            break;
        case VISITASANUAIS:
            printf("Quantas visitas anuais esse monumento recebe em media: ");
            scanf("%i", &(*deck)[indice].visitasAnuais);
            setbuf(stdin, NULL);
            break;
        case IMPORTANCIAHISTORICA:
            printf("De 0 a 10 qual a sua importancia historica: ");
            scanf("%i", &respostasAux);
            setbuf(stdin, NULL);
            while (respostasAux > 10 || respostasAux < 0)
            {
                printf("Resposta invalida!\nDigite novamente: ");
                scanf("%i", &respostasAux);
                setbuf(stdin, NULL);
            }
            (*deck)[indice].importanciaHistorica = respostasAux;
            break;
        case POPULARIDADE:
            printf("De 0 a 10 qual a sua popularidade: ");
            scanf("%i", &respostasAux);
            setbuf(stdin, NULL);
            while (respostasAux > 10 || respostasAux < 0)
            {
                printf("Resposta invalida!\nDigite novamente: ");
                scanf("%i", &respostasAux);
                setbuf(stdin, NULL);
            }
            (*deck)[indice].popularidade = respostasAux;
            break;
        }
        salvarNoCSV(deck, (*quantidadeCartas));
    }
    return;
}

void excluirCartas(cartas **deck, int *quantidadeCartas, int indice) {
   // Verifica se o índice é válido
   if (indice < 0 || indice >= *quantidadeCartas) {
       return;
   }
   for (int i = indice; i < (*quantidadeCartas) - 1; i++) {
       (*deck)[i] = (*deck)[i + 1];
   }
   (*quantidadeCartas)--;
   *deck = realloc(*deck, (*quantidadeCartas) * sizeof(cartas));
   bool temSuperTrunfo = false;
   for (int i = 0; i < *quantidadeCartas; i++) {
       if ((*deck)[i].supertrunfo == 1) {
           temSuperTrunfo = true;
           break;
       }
   }
   if (!temSuperTrunfo && *quantidadeCartas > 0) {
       (*deck)[0].supertrunfo = 1;
   }
   salvarNoCSV(deck, (*quantidadeCartas));
}

void salvarNoCSV(cartas **deck, int quantidadeCartas) {
    FILE *arq = fopen("deck.csv", "w");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo para salvar\n");
        return;
    }

    // Escreve os dados de cada carta
    for (int i = 0; i < quantidadeCartas; i++) {
        fprintf(arq, "%s,%c,%d,%d,%d,%d,%d,%d,%s\n",
                (*deck)[i].nome,
                (*deck)[i].letra,
                (*deck)[i].supertrunfo,
                (*deck)[i].anoConstrucao,
                (*deck)[i].altura,
                (*deck)[i].visitasAnuais,
                (*deck)[i].importanciaHistorica,
                (*deck)[i].popularidade,
                (*deck)[i].arqimg);
    }

    fclose(arq);
    return;
}