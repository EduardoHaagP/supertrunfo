#ifndef COMPARA_H
#define COMPARA_H

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

void read_cards(Card cards[], int *count);
void find_winner(Card cards[], int count);

#endif // COMPARA_H
