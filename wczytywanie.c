//
// Created by cheese on 08.04.2024.
//

#include "wczytywanie.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


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
    fseek(in, 12, SEEK_CUR);
    fread(counter, 4, 1, in);
    fseek(in, 6, SEEK_CUR);
    fread(path, 1, 1, in);
}

FILE* Konwertuj(FILE* in)
{
    short xyLabiryntu[2], xyStart[2], xyStop[2], xyKursor[2] = {1, 1};
    long counter;
    FILE* out = fopen("f.txt", "w");
    fseek(in, 5, SEEK_SET);
    fread(xyLabiryntu, 2, 2, in);
    fread(xyStart, 2, 2, in);
    fread(xyStop, 2, 2, in);
    fseek(in, 12, SEEK_CUR);
    fread(&counter, 4, 1, in);

    fseek(in, 7, SEEK_CUR);
    char symbol;
    unsigned char iloscSymboliWSlowie;


    while(counter)
    {
        fseek(in, 1, SEEK_CUR);
        fread(&symbol, 1, 1, in);
        fread(&iloscSymboliWSlowie, 1, 1, in);

        for(int i = 0; i <= iloscSymboliWSlowie; i++)
        {
            if(xyKursor[0]==xyStart[0]&&xyKursor[1]==xyStart[1])
                fprintf(out, "P");
            else if(xyKursor[0]==xyStop[0]&&xyKursor[1]==xyStop[1])
                fprintf(out, "K");
            else
                fprintf(out, "%c", symbol);

            if(xyKursor[0]==xyLabiryntu[0])
            {
                xyKursor[0] = 1;
                fprintf(out, "\n");
                xyKursor[1]++;
            }
            else
            xyKursor[0]++;
        }
        counter--;
    }
    fclose(in);
    fclose(out);
    in = fopen("f.txt", "rb");
    return in;
}

void PobierzWierszT(FILE* f, int xLabiryntu, int aktywnyWiersz, char** matrix, char** bufor)
{

    int symboleWWierszu = xLabiryntu*2 + 1;
    int target = (symboleWWierszu+1)*2*aktywnyWiersz;
    fseek(f, target, SEEK_SET);

    for(int i = 0; i < 3; i++)
    {
        fread(bufor[i], 1, symboleWWierszu, f);
        fgetc(f);
    }
    ZapiszWiersz(bufor, matrix, xLabiryntu);

}

void PobierzWierszB(FILE* in, int xLabiryntu, int aktywnyWiersz, char** matrix, char** bufor)
{

    short xyStart[2];
    short xyStop[2];
    fseek(in, 9, SEEK_SET);
    fread(xyStart, 2, 2, in);
    fread(xyStop, 2, 2, in);
    fseek(in, 23, SEEK_CUR);
    int symboleWWierszu = xLabiryntu * 2 + 1;
    int przebyteSymbole = 0;
    unsigned char iloscSymboliWSlowie;
    int target = aktywnyWiersz*2*symboleWWierszu;
    char symbol;
    int indeksX = 0, indeksY = 0;

    long start = clock();
    while(przebyteSymbole < target)
    {
        fseek(in, 2, SEEK_CUR);
        fread(&iloscSymboliWSlowie, 1, 1, in);
        przebyteSymbole += iloscSymboliWSlowie + 1;
    }
    long end = clock();
    printf("%ld ", end - start);


    if(przebyteSymbole > target)
    {
        fseek(in, -2, SEEK_CUR);
        fread(&symbol, 1, 1, in);
        for(int j = 0; j < przebyteSymbole - target; j++)
        {
            if(indeksX==xyStart[0]-1 && 2*aktywnyWiersz+indeksY == xyStart[1]-1)
                bufor[indeksY][indeksX] = 'P';
            else if(indeksX==xyStop[0]-1 && 2*aktywnyWiersz+indeksY == xyStop[1]-1)
                bufor[indeksY][indeksX] = 'K';
            else
                bufor[indeksY][indeksX] = symbol;
            indeksX++;
            if(indeksX==symboleWWierszu-1)
                {indeksX=0; indeksY++;}
        }
        fgetc(in);
    }
    przebyteSymbole -= target;
    target = 3*symboleWWierszu;

    while(przebyteSymbole < target)
    {
        fseek(in, 1, SEEK_CUR);
        fread(&symbol, 1, 1, in);
        fread(&iloscSymboliWSlowie, 1, 1, in);
        for(int i = 0; i <= iloscSymboliWSlowie; i++)
        {
            if(indeksX==xyStart[0]-1 && 2*aktywnyWiersz+indeksY == xyStart[1]-1)
                bufor[indeksY][indeksX] = 'P';
            else if(indeksX==xyStop[0]-1 && 2*aktywnyWiersz+indeksY == xyStop[1]-1)
                bufor[indeksY][indeksX] = 'K';
            else
                bufor[indeksY][indeksX] = symbol;
            indeksX++;
            if(indeksX==symboleWWierszu)
            {indeksX=0; indeksY++;}
            przebyteSymbole++;
        }
    }
//    FILE* out = fopen("f.txt", "w");
//    for(int j = 0; j < 3; j++)
//    {
//        for(int i = 0; i < symboleWWierszu; i++)
//        {
//            fprintf(out, "%c", bufor[j][i]);
//        }
//        fprintf(out, "\n");
//    }
//    fclose(out);
    ZapiszWiersz(bufor, matrix, xLabiryntu);


}
void ZapiszWiersz(char** bufor, char** matrix, int xLabiryntu)
{
    for(int i=0; i < xLabiryntu; i++)
    {
        matrix[i][0] = bufor[0][2*i+1];
        matrix[i][1] = bufor[1][2*i+2];
        matrix[i][2] = bufor[2][2*i+1];
        matrix[i][3] = bufor[1][2*i];
    }
//    for(int i = 0; i < xLabiryntu; i++)
//    {
//        printf("%3d ", i);
//        for(int j = 0; j < 4; j++)
//            printf("%c ", matrix[i][j]);
//        printf("\n");
//    }
}
