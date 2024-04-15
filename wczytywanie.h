//
// Created by cheese on 08.04.2024.
//

#ifndef LABIRYNT2_WCZYTYWANIE_H
#define LABIRYNT2_WCZYTYWANIE_H

#include <stdio.h>

//nie musisz rozumiec tego
#define USTAW_PRZEJSCIE(i,j) bufor[i][j] = fgetc(f)
#define ZAPISZ_SASIADOW(i)\
	{\
		USTAW_PRZEJSCIE(i,1);/*prawo*/\
		fseek(f, -3, SEEK_CUR);\
		USTAW_PRZEJSCIE(i,3);/*lewo*/\
		fseek(f, xLabiryntu*-2-2, SEEK_CUR);\
		USTAW_PRZEJSCIE(i,0);/*góra*/\
		fseek(f, xLabiryntu*4+3, SEEK_CUR);\
		USTAW_PRZEJSCIE(i,2);/*dół*/\
	}

short* PobierzWymiary(FILE* in);
void PobierzWiersz(FILE* f, int xLabiryntu, int aktywnyWiersz, char** bufor);


void PobierzDaneB(FILE* in, short* xyLabiryntu, short* xyStart, short* xyStop, long* counter, char* path);
void PobierzWierszB(FILE* in, short* xyLabiryntu, short aktywnyWiersz, char** bufor);

#endif //LABIRYNT2_WCZYTYWANIE_H
