#include "wyznacznik.h"

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
struct macierz zmniejszanie(struct macierz m, int a, int b);

float wyznacznik(struct macierz m)
{

    float suma = 0;
    if (m.kolumna != m.wiersz)
    {
        printf("nie mozna policzyc wyznacznika dla tej macierzy");
    }
    else
    {
        if (m.kolumna == 1)
        {
            return m.elementy[0];
        }
        else
        {
            for (int i = 0; i < m.wiersz; i++)
            {
                struct macierz m1 = zmniejszanie(m, 0, i);
                suma = suma + (powf(-1, i) * m.elementy[i] * wyznacznik(m1));
                //printf("%4.2f\n", suma);
                niszczenie(m1);
            }
            return suma;
        }
    }
}

struct macierz zmniejszanie(struct macierz m, int a, int b)
{
    struct macierz m1 = tworzenie(m.wiersz - 1, m.kolumna - 1);
    int k = 0;
    int x = 0;
    for (int i = 0; i < m.wiersz; i++)
    {
        for (int j = 0; j < m.kolumna; j++)
        {
            if (i == a || k - (i * m.kolumna) == b)
            {
                k++;
            }
            else
            {
                m1.elementy[x] = m.elementy[k];
                k++;
                x++;
            }
        }
    }
    return m1;
}
