//
// Created by cheese on 08.04.2024.
//

#include "wczytywanie.h"
#include <stdlib.h>
#include <stdio.h>

void PobierzWiersz(FILE* f, int xLabiryntu, int aktywnyWiersz, char** bufor)
{
    char c;

    fseek(f, 2*(1+2*aktywnyWiersz)*(xLabiryntu+1)+2, SEEK_SET);
    for(int i = 0; i < xLabiryntu; i++)
    {
        ZAPISZ_SASIADOW(i)
        fseek(f, xLabiryntu*-2, SEEK_CUR);
    }
}

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