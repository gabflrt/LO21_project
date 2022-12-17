#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "individu.h"
#include "population.h"

population inser_individu(population p, individu i)
{
    population m;
    if (p == NULL)
    {
        p = (Population *)malloc(sizeof(Population));
        p->individu = i;
        p->suivant = NULL;
        return p;
    }
    else
    {
        m = (Population *)malloc(sizeof(Population));
        m->individu = i;
        m->suivant = p;
        return m;
    }
}

population initialiser_population(population p)
{

    for (int j = 0; j < longPop; j++)
    {
        individu temp_individu = NULL;
        temp_individu = initialiser_individu(temp_individu, longIndiv);
        p = inser_individu(p, temp_individu);
    }
    return p;
}

population afficher_population(population p)
{
    if (p == NULL)
    {
        printf("La population est NULLE\n");
    }
    else
    {
        printf("Voici la population : \n");
        while (p != NULL)
        {
            afficher_individu(p->individu);
            printf("qualite : %2.2f\n", obtenir_qualite(p->individu));
            p = p->suivant;
        }
    }
}

int inferieur(population p, int e)
{
    population m = p;
    int trouve = 0;
    while (m != NULL)
    {
        if (obtenir_qualite(m->individu) > e)
        {
            trouve = 1;
        }
        m = m->suivant;
    }
    return trouve;
}

float milieu(float a, float b, float c)
{

    if ((a < b && a > c) || (a < c && a > b))
    {
        return a;
    }
    else if ((b < a && b > c) || (b < a && b > c))
    {
        return b;
    }
    else if (a == b)
    {
        if (a > c)
        {
            return a;
        }
        else
        {
            return c;
        }
    }
    else if (a == c)
    {
        if (b > a)
        {
            return b;
        }
        else
        {
            return a;
        }
    }
    else if (b == c)
    {
        if (a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
    else
    {
        return c;
    }
}

population trier_qualite(population p)
{
    // Sous populations
    population s1 = NULL;
    population s2 = NULL;
    // Position début milieu et fin pour choisir pivot
    population pd = p;
    population pm = p;
    population pf = p;
    // population temporaire
    population pt = p;
    float pivot;
    int taille = 0;
    // On s'occupe des cas triviaux
    if (p == NULL || p->suivant == NULL)
    {
        return p;
    }
    else if (p->suivant->suivant == NULL)
    {
        if (obtenir_qualite(p->individu) >= obtenir_qualite(p->suivant->individu))
        {
            return p;
        }
        else
        {
            s1 = inser_individu(s1, p->individu);
            s1 = inser_individu(s1, p->suivant->individu);
            return s1;
        }
    }
    else if ((p->suivant->suivant->suivant == NULL) && (obtenir_qualite(p->individu) == obtenir_qualite(p->suivant->individu)) && (obtenir_qualite(p->suivant->individu) == obtenir_qualite(p->suivant->suivant->individu)))
    {
        return p;
    }
    else
    {
        // CHOIX DU PIVOT
        // Dernière valeur de la liste
        while (pf->suivant != NULL)
        {
            pf = pf->suivant;
            taille++;
        }
        // Première valeur de la liste
        if (obtenir_qualite(pd->individu) == obtenir_qualite(pf->individu))
        {
            pd = pd->suivant;
        }
        // Valeur du milieu
        for (int i = 0; i < (taille / 2); i++)
        {
            pm = pm->suivant;
        }
        // Le pivot est la valeur centrale des trois pour avoir les meilleurs résultats
        pivot = milieu(obtenir_qualite(p->individu), obtenir_qualite(pm->individu), obtenir_qualite(pf->individu));
        // printf("pivot : %2.2f\n", pivot);
        //  Remplir les listes s1 et s2 en fonction de la valeur du pivot
        while (pt != NULL)
        {
            if (obtenir_qualite(pt->individu) >= pivot)
            {
                s1 = inser_individu(s1, pt->individu);
            }
            else
            {
                s2 = inser_individu(s2, pt->individu);
            }
            pt = pt->suivant;
        }

        // récursivité
        // printf("s1 :");
        // afficher_population(s1);
        s1 = trier_qualite(s1);

        // printf("s2 :");
        // afficher_population(s2);
        s2 = trier_qualite(s2);

        pt = s1;
        while (pt->suivant != NULL)
        {
            pt = pt->suivant;
        }
        pt->suivant = s2;

        return s1;
    }
}

population selectionner(population p, int tselect)
{
    population pt = p;
    population pt2 = p;
    for (int i = 0; i < tselect; i++)
    {
        pt = pt->suivant;
    }
    while (pt != NULL)
    {
        pt->individu = pt2->individu;
        pt = pt->suivant;
        pt2 = pt2->suivant;
    }
    return p;
}

population croiser_individus(individu i1, individu i2, float pcroiser)
{
    // Population renvoyé par la fonction, contenant les deux individus croisés
    population p = NULL;
    // Les deux individus croisés
    individu i3 = NULL;
    individu i4 = NULL;
    int tirage = rand() % 10;

    // Distribue les bits aux individu aléatoirement en fonction de la probabilité pcroiser
    for (int i = 0; i < longIndiv; i++)
    {
        tirage = rand() % 10;
        if (tirage < pcroiser * 10)
        {
            i3 = inser_bit(i3, i1->bit);
            i4 = inser_bit(i4, i2->bit);
        }
        else
        {
            i3 = inser_bit(i3, i2->bit);
            i4 = inser_bit(i4, i1->bit);
        }
        i1 = i1->suivant;
        i2 = i2->suivant;
    }

    // Insère les individus croisés dans la population pour les retourner
    p = inser_individu(p, i3);
    p = inser_individu(p, i4);
    return p;
}

population croiser_population(population p1)
{
    // Populations temporaires pour tirages aléatoires
    population pt1 = p1;
    population pt2 = p1;
    // Population reçu de la fonction croiser_individu
    population pc = NULL;
    // Population croiser renvoyé par la fonction
    population p2 = NULL;

    // Prendre aléatoirement deux individus dans la population
    int temp1 = rand() % longPop;
    int temp2 = rand() % longPop;

    for (int j = 0; j < longPop / 2; j++)
    {
        temp1 = rand() % longPop;
        temp2 = rand() % longPop;
        for (int i = 0; i < temp1; i++)
        {
            pt1 = pt1->suivant;
        }

        for (int i = 0; i < temp2; i++)
        {
            pt2 = pt2->suivant;
        }
        pc = croiser_individus(pt1->individu, pt2->individu, 0.5);

        p2 = inser_individu(p2, pc->individu);
        pc = pc->suivant;
        p2 = inser_individu(p2, pc->individu);
        pt1 = p1;
        pt2 = p1;
    }

    return p2;
}