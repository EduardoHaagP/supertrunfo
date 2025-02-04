#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cartas.h>

void find_winner(cartas carta1, cartas carta2, int atributo)
{
    int winner = -1;
    
    if (!carta1.supertrunfo == 1 && !carta2.supertrunfo == 1)
    {
    switch (atributo)
    {
    case 0: // Ano Contrucao
        if (carta1.anoConstrucao > carta2.anoConstrucao)
        {
            winner == 1;
        }else if (carta1.anoConstrucao < carta2.anoConstrucao)
        {
            winner == 2;
        }else{
            winner == 0;
        }
        break;
    case 1:// altura
        if (carta1.altura > carta2.altura)
        {
            winner == 1;
        }else if (carta1.altura < carta2.altura)
        {
            winner == 2;
        }else{
            winner == 0;
        }
        break;
    case 2:// visitas Anuais
        if (carta1.visitasAnuais > carta2.visitasAnuais)
        {
            winner == 1;
        }else if (carta1.visitasAnuais < carta2.visitasAnuais)
        {
            winner == 2;
        }else{
            winner == 0;
        }
        break;
    case 3:// Importancia Historica
        if (carta1.importanciaHistorica > carta2.importanciaHistorica)
        {
            winner == 1;
        }else if (carta1.importanciaHistorica < carta2.importanciaHistorica)
        {
            winner == 2;
        }else{
            winner == 0;
        }
        break;
    case 4:// Popularidade
        if (carta1.popularidade > carta2.popularidade)
        {
            winner == 1;
        }else if (carta1.popularidade < carta2.popularidade)
        {
            winner == 2;
        }else{
            winner == 0;
        }
        break;
    default:
        break;
    }
    }else if (carta1.supertrunfo == 1)
    {
        winner = 1;
    }else if (carta2.supertrunfo == 1)
    {
        winner = 2;
    }
    

    if (winner == 1)
    {
        printf("Winner: %s\n", carta1.nome);
    }
    if (winner == 2)
    {
        printf("Winner: %s\n", carta2.nome);
    }
    if (winner == 3)
    {
        printf("Empate\n");
    }
    return;
}