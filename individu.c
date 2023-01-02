#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "individu.h"

void afficher_individu(individu l)
{
    if (l == NULL)
    {
        printf("L'individu n'existe pas\n");
    }
    else
    {
        printf("Bits de l'individu : |");
        // Affiche 1 par 1 chaque bit de l'individu
        while (l != NULL)
        {
            printf(" %c |", l->bit);
            l = l->suivant;
        }
        printf("\n");
    }
}

int obtenir_longIndiv(individu l)
{
    if (l == NULL)
    {
        return 0;
    }
    else
    {
        // Calculer la longueur de l'individu
        int longueur = 0;
        while (l != NULL)
        {
            longueur++;
            l = l->suivant;
        }
        return longueur;
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

int obtenir_valeur(individu l)
{
    int valeur = 0;
    individu p = l;
    for (int i = obtenir_longIndiv(l); i > 0; i--)
    {
        valeur = valeur + ((p->bit) - 48) * pow(2, i - 1);
        p = p->suivant;
    }
    return valeur;
}

float obtenir_qualite(individu l)
{
    // Valeur pour les manipulations du 5.
    // float A = 0.1;
    // int B = 5;
    int A = -1;
    int B = 1;
    float X, qualite;
    int x = obtenir_valeur(l);
    // Formules pour les manipulations du 5.
    // qualite = -log(X);
    X = (x / pow(2, obtenir_longIndiv(l))) * (B - A) + A;
    qualite = -pow(X, 2);
    return qualite;
}

individu initialiser_individu(individu i, int longueur)
{
    int temp = 0;
    for (int j = 0; j < longueur; j++)
    {
        // Prendre aléatoirement nombre entre 48 et 49 qui correspondent aux caractères 0 et 1
        temp = rand() % 2 + 48;
        i = inser_bit(i, temp);
    }
    return i;
}