#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "raylib.h"
#include "visual.h"
#include "cartas.h"
#include "funcoes.h"
#include "jogar.h"

enum Opcoes
{
    SAIR = 0,
    INSERIR,
    LISTAR,
    PESQUISAR,
    ALTERAR,
    EXCLUIR,
};
//"deck.csv"

// Implementação das funções
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

//load
Fonte loadFonte()
{
    Fonte fonte;
    fonte.tituloCartas = LoadFont("./assets/font/Avenir-Black.ttf");
    fonte.tituloTelas = LoadFont("./assets/font/Avenir-Book.ttf");
    fonte.letraCarta = LoadFont("./assets/font/Avenir-Heavy.ttf");
    fonte.atributoCartas = LoadFont("./assets/font/AvenirNextCyr-Medium.ttf");
    return fonte;
}

void unloadFonte(Fonte font)
{
    UnloadFont(font.tituloCartas);
    UnloadFont(font.tituloTelas);
    UnloadFont(font.letraCarta);
    UnloadFont(font.atributoCartas);
    return;
}

Molduras loadMolduras()
{
    Molduras molduras;

    // Carrega as imagens e converte para texturas
    Image azul = LoadImage("./assets/moldura/azul.png");
    molduras.azul = LoadTextureFromImage(azul);
    UnloadImage(azul);

    Image azulST = LoadImage("./assets/moldura/azulST.png");
    molduras.azulST = LoadTextureFromImage(azulST);
    UnloadImage(azulST);

    Image verde = LoadImage("./assets/moldura/verde.png");
    molduras.verde = LoadTextureFromImage(verde);
    UnloadImage(verde);

    Image verdeST = LoadImage("./assets/moldura/verdeST.png");
    molduras.verdeST = LoadTextureFromImage(verdeST);
    UnloadImage(verdeST);

    Image amarelo = LoadImage("./assets/moldura/amarelo.png");
    molduras.amarelo = LoadTextureFromImage(amarelo);
    UnloadImage(amarelo);

    Image amareloST = LoadImage("./assets/moldura/amareloST.png");
    molduras.amareloST = LoadTextureFromImage(amareloST);
    UnloadImage(amareloST);

    Image vermelho = LoadImage("./assets/moldura/vermelho.png");
    molduras.vermelho = LoadTextureFromImage(vermelho);
    UnloadImage(vermelho);

    Image vermelhoST = LoadImage("./assets/moldura/vermelhoST.png");
    molduras.vermelhoST = LoadTextureFromImage(vermelhoST);
    UnloadImage(vermelhoST);

    return molduras;
}

void unloadMolduras(Molduras molduras)
{
    UnloadTexture(molduras.azul);
    UnloadTexture(molduras.verde);
    UnloadTexture(molduras.amarelo);
    UnloadTexture(molduras.vermelho);
    UnloadTexture(molduras.azulST);
    UnloadTexture(molduras.verdeST);
    UnloadTexture(molduras.amareloST);
    UnloadTexture(molduras.vermelhoST);
}

Textura loadTexturas(){
    Textura texturas;
    texturas.setaOFF = LoadTexture("./assets/textura/setasaidaOFF.png");
    texturas.setaON = LoadTexture("./assets/textura/setasaidaON.png");
    texturas.TexturaFundo = LoadTexture("./assets/textura/vector.png");
    texturas.editarOFF = LoadTexture("./assets/textura/editarOFF.png");
    texturas.editarON = LoadTexture("./assets/textura/editarON.png");
    
    return texturas;
    
}

void unloadTexturas(Textura texturas)
{
    UnloadTexture(texturas.setaOFF);
    UnloadTexture(texturas.setaON);
    UnloadTexture(texturas.TexturaFundo);
    return;
}

void loadIMGCartas(cartas *carta, int quantidadecartas){
    for (int i = 0; i < quantidadecartas; i++)
    {
        carta[i].img = LoadTexture(carta[i].arqimg);

        if (carta[i].img.id == 0)
        {
            // Handle the error (e.g., log it, return a default texture, etc.)
            printf("Failed to load texture: %s\n", carta[i].nome);
            // Optionally return a default texture or an empty texture
        }
    }

    // Check if the texture was loaded successfully

    return;
}
