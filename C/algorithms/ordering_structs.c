#include <stdio.h>
#include <stdlib.h>
#include "quick_sort.c"

typedef struct Anime
{
    char name[64];
    int yearOfRelease;
    int score;
} Anime;

void readInput(int size, Anime *animes[size])
{
    for (int i = 0; i < size; i++)
    {
        Anime *anime = malloc(sizeof(Anime));
        scanf("{ name: \"%[^\"]\", year: %d, score: %d },\n",
              anime->name, &anime->yearOfRelease, &anime->score);
        animes[i] = anime;
    }
}

int compareAnimeByScore(void *a, void *b)
{
    int aScore = ((Anime *)a)->score;
    int bScore = ((Anime *)b)->score;
    return aScore - bScore;
}

int main(void)
{
    Anime *animes[8];
    readInput(8, animes);
    void *animesVoid[8];
    for (int i = 0; i < 8; i++)
    {
        printf("name=%s\n", animes[i]->name);
        animesVoid[i] = (void *)animes[i];
    }
    quickSort(animesVoid, 0, 7, compareAnimeByScore);
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        printf("name=%s, score=%d\n", ((Anime *)animesVoid[i])->name, ((Anime *)animesVoid[i])->score);
    }

    return 0;
}