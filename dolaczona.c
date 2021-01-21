#include "wyznacznik.h"

struct macierz dolaczona(struct macierz m)
{
    struct macierz m1 = tworzenie(m.wiersz, m.kolumna);
    //struct macierz pom = tworzenie(m.wiersz-1,m.kolumna-1);
    int x = 0;
    for (int i = 0; i < m.wiersz; i++)
    {
        for (int j = 0; j < m.kolumna; j++)
        {
            struct macierz pom = zmniejszanie(m, i, j);
            //wypisz(pom);
            m1.elementy[x] = powf(-1, i + j) * wyznacznik(pom);
            x++;
            niszczenie(pom);
        }
    }
    return m1;
}

struct macierz transpozycja(struct macierz m)
{
    struct macierz m1 = tworzenie(m.wiersz, m.kolumna);
    int x = 0;
    for (int i = 0; i < m.wiersz; i++)
    {
        for (int j = 0; j < m.kolumna; j++)
        {
            m1.elementy[x] = m.elementy[j * m.wiersz + i];
            x++;
        }
    }
    return m1;
}

struct macierz dzielenie_przez_liczbe(struct macierz m, float liczba)
{
    struct macierz m2 = tworzenie(m.wiersz, m.kolumna);
    int x = 0;
    for (int i = 0; i < m2.wiersz; i++)
    {
        for (int j = 0; j < m2.kolumna; j++)
        {
            m2.elementy[x] = m.elementy[x] / liczba;
            //printf("%4.2f\n", m.elementy[x] / liczba);
            x++;
        }
    }
    return m2;
}

struct macierz mnozenie(struct macierz m1, struct macierz m2)
{
    struct macierz wynik = tworzenie(m1.wiersz, m2.kolumna);
    int x = 0;
    //printf("zyje\n");
    for (int i = 0; i < m1.wiersz; i++)
    {
        for (int j = 0; j < m1.kolumna; j++)
        {
            float pom = 0;
            for (int k = 0; k < m1.kolumna; k++)
            {
                //printf("zyje\n");
                //printf("%d ", wynik.kolumna);
                pom = pom + (m1.elementy[i * m1.kolumna + k] * m2.elementy[k * m1.kolumna + j]);
                //printf("%4.2f\n", pom);
            }
            //printf("\n");
            wynik.elementy[x] = pom;
            x++;
        }
    }
    return wynik;
}

struct macierz losowa()
{
    int zarodek;
    time_t tt;
    zarodek = time(&tt);
    srand(zarodek);
    int wymiar = 1 + rand() % 10;
    struct macierz m = tworzenie(wymiar, wymiar);
    for (int i = 0; i < wymiar * wymiar; i++)
    {
        m.elementy[i] = rand() % 100;
    }
    return m;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 1; i++)
    {
        //struct macierz mac = odczyt("macierz.txt");
        struct macierz mac = losowa();
        printf("macierz losowa o wymiarach %dx%d to:\n", mac.wiersz, mac.kolumna);
        wypisz(mac);
        struct macierz mac1 = dolaczona(mac);
        printf("macierz dolaczona:\n");
        wypisz(mac1);
        struct macierz mac2 = transpozycja(mac1);
        printf("transpozycja macierzy dolaczonej\n");
        wypisz(mac2);
        printf("wyznacznik macierzy = %4.2f\n", wyznacznik(mac));
        struct macierz mac4 = dzielenie_przez_liczbe(mac2, wyznacznik(mac));
        printf("macierz odwrotna:\n");
        wypisz(mac4);
        printf("wynik manozenia macierzy i macierzy odwrotnej:\n");
        struct macierz mac3 = mnozenie(mac, mac4);
        wypisz(mac3);
        // printf("macierz losowa:\nwymiary macierzy : %dx%d",);
        //struct macierz los = losowa();
        //printf("macierz losowa:\nwymiary macierzy : %dx%d\n", los.wiersz, los.kolumna);
        //wypisz(los);
        //niszczenie(los);
        niszczenie(mac3);
        niszczenie(mac4);
        niszczenie(mac);
        niszczenie(mac2);
        niszczenie(mac1);
    }
}