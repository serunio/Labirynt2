//
// Created by cheese on 08.04.2024.
//

#ifndef LABIRYNT2_WCZYTYWANIE_H
#define LABIRYNT2_WCZYTYWANIE_H

#include <stdio.h>

short* PobierzWymiary(FILE* in);

void PobierzDaneB(FILE* in, short* xyLabiryntu, short* xyStart, short* xyStop, long* counter, char* path);
FILE* Konwertuj(FILE* in);

void PobierzWierszT(FILE* f, int xLabiryntu, int aktywnyWiersz, char** matrix, char** bufor);
void ZapiszWiersz(char** bufor, char** matrix, int xLabiryntu);
void PobierzWierszB(FILE* in, int xLabiryntu, int aktywnyWiersz, char** matrix, char** bufor);

#endif //LABIRYNT2_WCZYTYWANIE_H
