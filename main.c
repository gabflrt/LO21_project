#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "individu.h"
#include "population.h"

int main()
{
    // Initialiser la Population
    printf("\n\n------------ Initialisation de la population -----------\n");
    population population1 = NULL;
    afficher_population(population1);
    population1 = initialiser_population(population1);
    afficher_population(population1);

    // Croiser la population
    printf("\n\n------------ Croiser la population -----------\n");
    population1 = croiser_population(population1);
    afficher_population(population1);

    // Trier la population avec QuickSort
    printf("\n\n------------ Tri de la population -----------\n");
    population1 = trier_qualite(population1);
    afficher_population(population1);

    // Selectionner la population
    printf("\n\n------------ Selection de la population -----------\n");
    population1 = selectionner(population1, 4);
    afficher_population(population1);

    // Afficher le meilleur individu de la Population
    printf("\n\n------------ Meilleur individu de la population -----------\n");
    afficher_individu(population1->individu);
}
