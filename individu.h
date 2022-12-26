#ifndef INDIVIDU_H
#define INDIVIDU_H

typedef unsigned char Bit;

typedef struct indiv
{
    Bit bit;
    struct indiv *suivant;
} Individu;

typedef Individu *individu;

void afficher_individu(individu l);
int obtenir_longIndiv(individu l);
individu inser_bit(individu l, int v);
int obtenir_valeur(individu l);
float obtenir_qualite(individu l);
individu initialiser_individu(individu i, int longueur);

#endif