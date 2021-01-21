#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct macierz
{
    int wiersz;
    int kolumna;
    float *elementy;
};

struct macierz tworzenie(int wiersz, int kolumna)
{
    struct macierz m =
        {
            wiersz,
            kolumna,
            calloc(kolumna * wiersz, sizeof(float))};
    return m;
}

struct macierz odczyt(char nazwa[])
{
    FILE *plik = fopen(nazwa, "r");
    int k = 0, w = 0;
    fscanf(plik, "%d", &w);
    fscanf(plik, "%d", &k);
    //printf("%d\n%d\n", w, k);
    //printf("%d", w * k);
    struct macierz m = tworzenie(w, k);
    //printf("%d", w * k);
    for (int i = 0; i < w * k; i++)
    {
        fscanf(plik, "%f ", &m.elementy[i]);
        //printf("%f ", m.elementy[i]);
    }
    fclose(plik);
    return m;
}

void wypisz(struct macierz m)
{
    for (int i = 0; i < m.wiersz; i++)
    {
        for (int j = 0; j < m.kolumna; j++)
        {
            printf("%6.2f", m.elementy[i * m.kolumna + j]);
        }
        printf("\n");
    }
}
void niszczenie(struct macierz m)
{
    free(m.elementy);
}

void zapis(struct macierz m, char nazwa[])
{
    FILE *plik = fopen(nazwa, "w+");
    fprintf(plik, "%d\n%d\n", m.wiersz, m.kolumna);
    for (int i = 0; i < m.wiersz; i++)
    {
        for (int j = 0; j < m.kolumna; j++)
        {
            fprintf(plik, "%6.2f", m.elementy[i * m.kolumna + j]);
        }
        fprintf(plik, "\n");
    }
    fclose(plik);
}

int main(int argc, char *argv[])
{
    struct macierz m = tworzenie(atol(argv[1]), atol(argv[2]));
    zapis(m, "macierz.txt");
    struct macierz m1 = odczyt("macierz.txt");
    printf("%d\n%d\n", m1.wiersz, m1.kolumna);
    wypisz(m);
    zapis(m1, "macierz1.txt");
    niszczenie(m1);
    niszczenie(m);
    //wypisz(m1);
    //zapis(m1, argv[2]);
    //niszczenie(m1);
    return 0;
}
