//
// Created by cheese on 08.04.2024.
//

#include "wczytywanie.h"
#include <stdlib.h>
#include <stdio.h>

void PobierzWiersz(FILE* f, int xLabiryntu, int aktywnyWiersz, char** bufor)
{
    fseek(f, 2*(1+2*aktywnyWiersz)*(xLabiryntu+1)+2, SEEK_SET);
    for(int i = 0; i < xLabiryntu; i++)
    {
        ZAPISZ_SASIADOW(i)
        fseek(f, xLabiryntu*-2, SEEK_CUR);
    }
}

///DO ZROBIENIA
///zastąpić PobierzSzerokość() i PobierzWysokość jedną funkcją PobierzWymiary()
int PobierzSzerokosc(FILE* in)
{
    int xLabiryntu = 0;
    while(fgetc(in) != '\n')
        xLabiryntu++;

    //xLabiryntu zawiera zarowno komorki i sciany, wiec trzeba odjac jedna sciane i podzielic na 2
    xLabiryntu -= 1;
    xLabiryntu /= 2;
    return xLabiryntu;
}

int PobierzWysokosc(FILE* in)
{
    int yLabiryntu = 1;
    int c;
    while((c=fgetc(in))!=EOF)
        if(c=='\n') yLabiryntu++;
    yLabiryntu -= 1;
    yLabiryntu /= 2;
    return yLabiryntu;
}

void PobierzDaneB(FILE* in, int* yxLabiryntu, int* yxStart, int* yxStop, long* counter)
{
    short bufor;

    fseek(in, 5, SEEK_SET);
    fread(&bufor, 2, 1, in);
    bufor -= 1; bufor /= 2;
    yxLabiryntu[1] = bufor;

    fseek(in, 7, SEEK_SET);
    fread(&bufor, 2, 1, in);
    bufor -= 1; bufor /= 2;
    yxLabiryntu[0] = bufor;

    ///DO ZROBIENIA:
    ///pobranie yxStart, yxStop i counter
}

void PobierzWierszB(FILE* in, int xLabiryntu, int aktywnyWiersz, char** bufor, long* counter)
{
    ///DO ZROBIENIA
}
