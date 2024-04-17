#include "wczytywanie.h"
#include "dfs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    char tryb = argc > 2 ? argv[1][0] : 0;
    FILE* in = argc > 2 ? fopen(argv[2], "rb") : NULL;
    if(in==NULL || (tryb!='b'&&tryb!='t'))
    {
        printf("Niepoprawne argumenty\n");
        return 1;
    }
    short* xyLabiryntu = malloc(2*sizeof(short));
    short* xyStart = malloc(2*sizeof(short));
    short* xyStop = malloc(2*sizeof(short));
    char path;
    long counter;

    if(tryb=='b')
        //PobierzDaneB(in, xyLabiryntu, xyStart, xyStop, &counter, &path);
    {in = Konwertuj(in);}
    //if(tryb=='t')
        //pobranie wymiarów labiryntu (0:x, 1:y)
        xyLabiryntu = PobierzWymiary(in);

    //macierz buforujaca czesc labiryntu, w ktorej:
    //y - komorki w rzedzie
    char** matrix = malloc(xyLabiryntu[0] * sizeof(char*));
    for(int i = 0; i < xyLabiryntu[0]; i++)
        //x - informacja o tym w ktora strone mozna przejsc:
        //góra, prawo, lewo, dół
        matrix[i] = malloc(4*sizeof(char));
    char** bufor = malloc(3*sizeof(char*));
    for(int i = 0; i < 3; i++)
        bufor[i] = malloc((1+2*xyLabiryntu[0])*sizeof(char));

    short xyAktywnaKomorka[2] = {(short)(xyLabiryntu[0] - 1), (short)(xyLabiryntu[1] - 1)}; //położenie x,y

    //reszta z dzielenia przez 4 ze zwrot to kierunek w którym patrzy program
    //0 - góra, 1 - prawo, 2 - dół, 3 - lewo
    int zwrot = 4000;
    int droga = 0;
    //PobierzWierszB(in, xyLabiryntu[0], 0, matrix, bufor);
    printf("START\n");
    DFS(in, xyLabiryntu, xyAktywnaKomorka, zwrot, &droga, matrix, bufor, 't');
    printf("FORWARD %i \nSTOP\n", droga);


    fclose(in);
    for(int i = 0; i < xyLabiryntu[0]; i++)
        free(matrix[i]);
    for(int i = 0; i < 3; i++)
        free(bufor[i]);
    free(bufor);
    free(matrix);
    free(xyLabiryntu);
    free(xyStop);
    free(xyStart);
}
