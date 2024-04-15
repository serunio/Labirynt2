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

short* PobierzWymiary(FILE* in)
{
    short* xyLabiryntu = malloc(2 * sizeof(short));
    xyLabiryntu[0] = 0; //x
    while(fgetc(in) != '\n')
        xyLabiryntu[0]++;

    //xLabiryntu zawiera zarowno komorki i sciany, wiec trzeba odjac jedna sciane i podzielic na 2
    xyLabiryntu[0] -= 1;
    xyLabiryntu[0] /= 2;

    xyLabiryntu[1] = 1; //y
    int c;
    while((c=fgetc(in))!=EOF)
        if(c=='\n') xyLabiryntu[1]++;
    xyLabiryntu[1] -= 1;
    xyLabiryntu[1] /= 2;

    return xyLabiryntu;
}

void PobierzDaneB(FILE* in, short* xyLabiryntu, short* xyStart, short* xyStop, long* counter, char* path)
{
    fseek(in, 5, SEEK_SET);
    fread(xyLabiryntu, 2, 2, in);
    xyLabiryntu[0] -= 1; xyLabiryntu[0] /= 2;
    xyLabiryntu[1] -= 1; xyLabiryntu[1] /= 2;
    fread(xyStart, 2, 2, in);
    fread(xyStop, 2, 2, in);
    xyStart[0]++; xyStart[0] /= 2; xyStart[1] /= 2;
    xyStop[0] /= 2; xyStop[1] /= 2;
    fseek(in, 12, SEEK_CUR);
    fread(counter, 4, 1, in);
    fseek(in, 6, SEEK_CUR);
    fread(path, 1, 1, in);
}

void PobierzWierszB(FILE* in, short* xyLabiryntu, short aktywnyWiersz, char** bufor)
{
    FILE* out = fopen("f.txt", "w");
    fseek(in, 40, SEEK_SET);
    int symboleWWierszu = xyLabiryntu[0] * 2 + 1;
    int przebyteSymbole = 0;
    unsigned char symboleWSlowie;
    int target = aktywnyWiersz*2*symboleWWierszu;
    char symbol;
    while(przebyteSymbole < target)
    {
        fseek(in, 2, SEEK_CUR);
        fread(&symboleWSlowie, 1, 1, in);
        przebyteSymbole += symboleWSlowie + 1;
    }
    if(target < przebyteSymbole)
    {
        fseek(in, -2, SEEK_CUR);
        fread(&symbol, 1, 1, in);
        for(int j = 0; j < przebyteSymbole - target; j++)
        {
            fprintf(out, "%c", symbol);
        }
        fgetc(in);
    }
    target = 3*symboleWWierszu;
    przebyteSymbole = 0;
    while(przebyteSymbole < target)
    {
        fseek(in, 1, SEEK_CUR);
        fread(&symbol, 1, 1, in);
        fread(&symboleWSlowie, 1, 1, in);

        for(int i = 0; i <= symboleWSlowie; i++)
        {
            fprintf(out, "%c",
                    aktywnyWiersz==0 && przebyteSymbole==symboleWWierszu ? 'P'
                    : aktywnyWiersz==xyLabiryntu[1]-1 && przebyteSymbole==2*symboleWWierszu-1 ? 'K'
                    : symbol);
            przebyteSymbole++;
            if(!(przebyteSymbole%symboleWWierszu))
                fprintf(out, "\n");
        }
    }
    fclose(out);

    FILE* in2 = fopen("maze.txt", "rb");
    PobierzWiersz(in2, xyLabiryntu[0], 0, bufor);

    fclose(in2);
}
