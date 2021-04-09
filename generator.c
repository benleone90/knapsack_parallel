#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void weights(int w[])
{
    int i;
    if (w == NULL)
    {
        printf("Memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        srand(12);
        for (i = 0; i < ITEMS; i++)
        {
            w[i] = (rand() % (MAXW - MINW + 1)) + MINW;
        }
    }
}

void values(int v[])
{
    int i;
    if (v == NULL)
    {
        printf("Memory not allocated\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        srand(18);
        for (i = 0; i < ITEMS; i++)
        {
            v[i] = (rand() % (MAXW - MINW + 1)) + MINW;
        }
    }
}

int generator(int w[], int v[])
{
    weights(w);
    values(v);
    return 0;
}