#ifndef WYZNACZNIK_H
#define WYZNACZNIK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct macierz
{
    int wiersz;
    int kolumna;
    float *elementy;
};
struct macierz tworzenie(int wiersz, int kolumna);
struct macierz odczyt(char nazwa[]);
void wypisz(struct macierz m);
void niszczenie(struct macierz m);
void zapis(struct macierz m, char nazwa[]);
struct macierz zmniejszanie(struct macierz m, int a, int b);
float wyznacznik(struct macierz m);

#endif