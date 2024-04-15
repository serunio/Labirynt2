#include "wczytywanie.h"
#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE* in = fopen("..\\maze.txt", "rb");
    int x = PobierzSzerokosc(in);
    //pobranie wymiarów labiryntu (0:y, 1:x)
    int yxLabiryntu[2];
    yxLabiryntu[0] = PobierzWysokosc(in);
    yxLabiryntu[1] = x;

    //macierz buforujaca czesc labiryntu, w ktorej:
    //y - komorki w rzedzie
    char** matrix = malloc(yxLabiryntu[1]*sizeof(char*));
    for(int i = 0; i < yxLabiryntu[1]; i++)
        //x - informacja o tym w ktora strone mozna przejsc:
        //góra, prawo, lewo, dół
        matrix[i] = malloc(4*sizeof(char));

    int yxAktywnaKomorka[2] = {yxLabiryntu[0] - 1, yxLabiryntu[1] - 1}; //położenie y,x

    //reszta z dzielenia przez 4 ze zwrot to kierunek w którym patrzy program
    //0 - góra, 1 - prawo, 2 - dół, 3 - lewo
    int zwrot = 4003;
    int droga = 0;
    printf("START\n");
    DFS(in, yxLabiryntu[1], yxAktywnaKomorka, zwrot, &droga, matrix);
    printf("FORWARD %i \nSTOP\n", droga);


    fclose(in);
    for(int i = 0; i < yxLabiryntu[1]; i++)
        free(matrix[i]);
    free(matrix);
}
