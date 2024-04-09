//
// Created by cheese on 09.04.2024.
//

#include "dfs.h"
#include "wczytywanie.h"
#include <stdio.h>

int DFS(FILE* f, int xLabiryntu, int* aktywnaKomorka, int zwrot, char** wiersz)
{

    PobierzWiersz(f, xLabiryntu, aktywnaKomorka[0], wiersz);
    int x = aktywnaKomorka[1], y = aktywnaKomorka[0];
    if (wiersz[ aktywnaKomorka[1] ][ 1 ] == 'K')
    {
        printf("[%d %d] ", x, y);
        return 1;
    }

    //obrot w prawo
    zwrot++;

    for(int i = 0; i<=2; i++)
    {

        if (wiersz[aktywnaKomorka[1]][zwrot % 4] == ' ')
        {

            switch(zwrot%4)
            {
                case 0:
                    aktywnaKomorka[0]--;
                    break;
                case 1:
                    aktywnaKomorka[1]++;
                    break;
                case 2:
                    aktywnaKomorka[0]++;
                    break;
                case 3:
                    aktywnaKomorka[1]--;
                    break;
            }
            if(DFS(f, xLabiryntu, aktywnaKomorka, zwrot, wiersz))
            {
                printf("[%d %d] ", x, y);
                return 1;
            }
            aktywnaKomorka[0]=y; aktywnaKomorka[1]=x;
            PobierzWiersz(f, xLabiryntu, aktywnaKomorka[0], wiersz);
        }

        //obrót w lewo
        zwrot--;
    }
    return 0;
}
