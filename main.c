#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//enum para facilitar manutenção cogido menu
enum Opcoes{SAIR = 0, JOGAR, DECKS};

 typedef struct
{
    char nome[51];
    char pais[51];
    int anoConstrucao;
    float altura;
    int visitasAnuais;
    int importanciaHistorica;
    int popularidade;
}cartas;

void jogar(){
    printf("Em Breve\n");
    return;
}

void decks(){
    printf("Em Breve\n");
    return;
}

void menu(int *vmenu){
    printf("1 - Jogar\n2 - Decks\n0 - Sair");
    scanf("%i",&vmenu);
    return;
}

int main()
{
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
    
    default:
        printf("O valor digitado não é valido\n");
        break;
    }
    } while (vmenu != SAIR);
    return 0;
}