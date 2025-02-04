#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS 100
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char category;
    int year;
    int height;
    int cost;
    int attribute1;
    int attribute2;
} Card;

void read_cards(Card cards[], int *count) {
    FILE *file = fopen("deck.csv", "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    *count = 0;
    while (fscanf(file, "%99[^,],%c,%*d,%d,%d,%d,%d,%d,%*s\n",
                  cards[*count].name,
                  &cards[*count].category,
                  &cards[*count].year,
                  &cards[*count].height,
                  &cards[*count].cost,
                  &cards[*count].attribute1,
                  &cards[*count].attribute2) == 7) {
        (*count)++;
    }

    fclose(file);
}

void find_winner(Card cards[], int count) {
    int max_index = 0;
    for (int i = 1; i < count; i++) {
        if (cards[i].height > cards[max_index].height) {
            max_index = i;
        }
    }
    printf("Winner: %s\n", cards[max_index].name);
    printf("Height: %d m\n", cards[max_index].height);
    printf("Cost: %d\n", cards[max_index].cost);
}