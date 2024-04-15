//
// Created by cheese on 09.04.2024.
//

#include "dfs.h"
#include "wczytywanie.h"
#include <stdio.h>

int DFS(FILE* f, short* xyLabiryntu, short* xyAktywnaKomorka, int zwrot, int* droga, char** wiersz, char tryb)
{
    if(tryb=='t')
        PobierzWiersz(f, xyLabiryntu[0], xyAktywnaKomorka[1], wiersz);
    else if(tryb=='b')
        PobierzWierszB(f, xyLabiryntu, xyAktywnaKomorka[1], wiersz);
    else return 0;
    short x = xyAktywnaKomorka[0], y = xyAktywnaKomorka[1];
    int zwrot0 = zwrot;

    //obrot w prawo
    zwrot++;

    for(int i = 0; i<=2; i++)
    {
        if (wiersz[ xyAktywnaKomorka[0] ][ zwrot % 4 ] == 'P')
            return 1;
        if (wiersz[xyAktywnaKomorka[0]][zwrot % 4] == ' ')
        {
            switch(zwrot%4)
            {
                case 0:
                    xyAktywnaKomorka[1]--;
                    break;
                case 1:
                    xyAktywnaKomorka[0]++;
                    break;
                case 2:
                    xyAktywnaKomorka[1]++;
                    break;
                case 3:
                    xyAktywnaKomorka[0]--;
                    break;
            }
            if(DFS(f, xyLabiryntu, xyAktywnaKomorka, zwrot, droga, wiersz, tryb))
            {
                (*droga)++;
                //printf("%i ", *droga);
                switch(zwrot0-zwrot)
                {
                    case -1:
                        printf("FORWARD %i \n", *droga);
                        *droga=0;
                        printf("TURN LEFT \n");

                        break;
                    case 1:
                        printf("FORWARD %i \n", *droga);
                        *droga=0;
                        printf("TURN RIGTH \n");

                        break;
                    default:
                        ;
                }
                //printf("[%d %d] ", x, y);
                return 1;
            }
            xyAktywnaKomorka[1]=y; xyAktywnaKomorka[0]=x;
            if(tryb=='t')
                PobierzWiersz(f, xyLabiryntu[0], xyAktywnaKomorka[1], wiersz);
            else if(tryb=='b')
                PobierzWierszB(f, xyLabiryntu, xyAktywnaKomorka[1], wiersz);
        }

        //obrót w lewo
        zwrot--;
    }
    return 0;
}
