#ifndef POPULATION_H
#define POPULATION_H

#include "individu.h"

// Définition du type abstrait de données appelé Population
typedef struct pop
{
    Individu *individu;
    struct pop *suivant;
} Population;

typedef Population *population;

population inser_individu(population p, individu i);
population initialiser_population(population p, int longPop, int longIndiv);
void afficher_population(population p);
int obtenir_longPop(population p);
int inferieur(population p, int e);
float milieu(float a, float b, float c);
population trier_qualite(population p);
population selectionner(population p, int tselect);
population croiser_individus(individu i1, individu i2, float pcroiser);
population croiser_population(population p1, float pcroiser);
#endif