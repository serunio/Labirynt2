#include "wczytywanie.h"
#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE* in = fopen("..\\maze.txt", "rb");

    //pobranie szerokosci labiryntu
    int xLabiryntu = PobierzSzerokosc(in);

    //macierz buforujaca czesc labiryntu, w ktorej:
    //y - komorki w rzedzie
    char** matrix = malloc(xLabiryntu*sizeof(char*));
    for(int i = 0; i < xLabiryntu; i++)
        //x - informacja o tym w ktora strone mozna przejsc:
        //prawo, lewo, góra, dół
        matrix[i] = malloc(4*sizeof(char));

    int aktywnaKomorka[2] = {0,0}; //położenie y,x

    PobierzWiersz(in, xLabiryntu, aktywnaKomorka[0], matrix);

    //
    int zwrot = 4001;

    DFS(in, xLabiryntu, aktywnaKomorka, zwrot, matrix);

    fclose(in);
    for(int i = 0; i < xLabiryntu; i++)
        free(matrix[i]);
    free(matrix);
}