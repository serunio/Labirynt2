//
// Created by cheese on 09.04.2024.
//

#include "dfs.h"
#include "wczytywanie.h"
#include <stdio.h>

int DFS(FILE* f, int xLabiryntu, int* yxAktywnaKomorka, int zwrot, int* droga, char** wiersz)
{

    PobierzWiersz(f, xLabiryntu, yxAktywnaKomorka[0], wiersz);
    int x = yxAktywnaKomorka[1], y = yxAktywnaKomorka[0], zwrot0 = zwrot;
    if (wiersz[ yxAktywnaKomorka[1] ][ 3 ] == 'P')
    {
        //printf("[%d %d] ", x, y);
        return 1;
    }

    //obrot w prawo
    zwrot++;

    for(int i = 0; i<=2; i++)
    {
        if (wiersz[yxAktywnaKomorka[1]][zwrot % 4] == ' ')
        {
            switch(zwrot%4)
            {
                case 0:
                    yxAktywnaKomorka[0]--;
                    break;
                case 1:
                    yxAktywnaKomorka[1]++;
                    break;
                case 2:
                    yxAktywnaKomorka[0]++;
                    break;
                case 3:
                    yxAktywnaKomorka[1]--;
                    break;
            }
            if(DFS(f, xLabiryntu, yxAktywnaKomorka, zwrot, droga, wiersz))
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
            yxAktywnaKomorka[0]=y; yxAktywnaKomorka[1]=x;
            PobierzWiersz(f, xLabiryntu, yxAktywnaKomorka[0], wiersz);
        }

        //obrót w lewo
        zwrot--;
    }
    return 0;
}
