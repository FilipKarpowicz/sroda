#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 3

struct macierz
{
    float elementy[N][N];
};

struct macierz dodaj(struct macierz A, struct macierz B)
{
    struct macierz suma;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            suma.elementy[i][j] = A.elementy[i][j] + B.elementy[i][j];
    return suma;
}

struct macierz nowa(struct macierz A, int rozmiar, int k, int w)
{
    struct macierz wynik;
    int a = w, b = k;
    for (int i = 0; i < rozmiar - 1; i++)
    {
        if (i != w)
        {
            for (int j = 0; j < rozmiar - 1; j++)
            {
                if (j != k)
                {
                    wynik.elementy[i][j] = A.elementy[a][b];
                }
                w++;
            }
        }
        b++;
    }
    return wynik;
}

float wyznacznik(int k, struct macierz A, int w, float suma, int rozmiar)
{
    //struct macierz B;
    if (rozmiar == 2)
        return (A.elementy[w][k] * A.elementy[w + 1][k + 1]) - (A.elementy[w + 1][k] * A.elementy[w][k + 1]);
    for (int i = 0; i < rozmiar - 1; i++)
    {
        suma = suma + (pow((-1), w + k) * A.elementy[i][k] * wyznacznik(k + 1, nowa(A, rozmiar, k + 1, i + 1), w + 1, suma, rozmiar - 1));
    }
    return suma;
}

struct macierz transpozycja(struct macierz A)
{
    struct macierz wynik;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            wynik.elementy[i][j] = A.elementy[j][i];
        }
    return wynik;
}

void wypisz(struct macierz suma)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%4.1f", suma.elementy[i][j]);
        printf("\n");
    }
}
struct macierz odejmowanie(struct macierz A, struct macierz B)
{
    struct macierz suma;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            suma.elementy[i][j] = A.elementy[i][j] - B.elementy[i][j];
    return suma;
}

struct macierz mnozenie(struct macierz A, struct macierz B)
{
    struct macierz suma;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            float pom = 0;
            for (int k = 0; k < N; k++)
            {
                pom = pom + (A.elementy[i][k] * B.elementy[k][j]);
            }
            suma.elementy[i][j] = pom;
        }
    return suma;
}

void zapisz(FILE *plik, struct macierz A)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fprintf(plik, "%4.1f", A.elementy[i][j]);
        }
        fprintf(plik, "\n");
    }
}

struct macierz odczyt(FILE *plik2, int wiersz, int kolumna)
{
    struct macierz wynik;
    float liczba;
    for (int i = 0; i < wiersz; i++)
        for (int j = 0; j < kolumna; j++)
        {
            fscanf(plik2, "%f", &liczba);
            wynik.elementy[i][j] = liczba;
            //printf("%d %d %f", i, j, liczba);
        }
    return wynik;
}

int main(int argc, char *argv[])
{
    FILE *plik, *plik2;
    plik2 = fopen("macierz.txt", "r");
    plik = fopen("wynik.txt", "w+");
    struct macierz A = {1, 2, 3, 1, 2, 3, 1, 2, 3};
    struct macierz B = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    struct macierz suma = mnozenie(A, B);
    float w = wyznacznik(0, A, 0, 0, N);
    //wypisz(A);
    //wypisz(B);
    // wypisz(suma);
    //wypisz(odczyt(plik2, N, N));
    printf("%4.2f\n", w);
    // wypisz(transpozycja(A));
    // zapisz(plik, A);
    fclose(plik);
    fclose(plik2);
    return 0;
}