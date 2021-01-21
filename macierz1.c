#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef float macierz[N][N];

void wypisz(macierz m)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%4.0f", m[i][j]);
        }
        printf("\n");
    }
}
int main(int argc, char *argv[])
{
    macierz m = {0, 0, 5, 0, 3, 0, 0, 0, 1};
    wypisz(m);
}
