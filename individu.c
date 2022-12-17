#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "individu.h"

individu afficher_individu(individu l)
{
    if (l == NULL)
    {
        printf("L'individu n'existe pas\n");
    }
    else
    {
        printf("Bits de l'individu : |");
        while (l != NULL)
        {
            printf(" %c |", l->bit);
            l = l->suivant;
        }
        printf("\n");
    }
}

individu inser_bit(individu l, int v)
{
    individu p = l;
    individu m;
    if (l == NULL)
    {
        l = (Individu *)malloc(sizeof(Individu));
        l->bit = v;
        l->suivant = NULL;
        return l;
    }
    else
    {
        m = (Individu *)malloc(sizeof(Individu));
        m->bit = v;
        m->suivant = NULL;
        while (p->suivant != NULL)
        {
            p = p->suivant;
        }
        p->suivant = m;
        return l;
    }
}

float obtenir_valeur(individu l)
{
    int valeur = 0;
    individu p = l;
    for (int i = longIndiv; i > 0; i--)
    {
        valeur = valeur + ((p->bit) - 48) * pow(2, i - 1);
        p = p->suivant;
    }
    return valeur;
}

float obtenir_qualite(individu l)
{
    int A = -1;
    int B = 1;
    float X, qualite;
    float x = obtenir_valeur(l);
    X = (x / pow(2, longIndiv)) * (B - A) + A;
    qualite = -pow(X, 2);
    return qualite;
}

individu initialiser_individu(individu i, int longIndiv)
{
    // n = (7 ^ 5 * n) % (2 ^ 31 - 1);
    // srand(n);
    int temp = 0;
    for (int j = 0; j < longIndiv; j++)
    {
        temp = rand() % 2 + 48;
        // printf("La valeur est : %d\n",temp);
        i = inser_bit(i, temp);
    }
    return i;
}