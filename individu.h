#ifndef INDIVIDU_H
#define INDIVIDU_H

int longIndiv = 8;

typedef unsigned char Bit;

typedef struct indiv
{
    Bit bit;
    struct indiv *suivant;
} Individu;

typedef Individu *individu;

individu afficher_individu(individu l);
individu inser_bit(individu l, int v);
float obtenir_valeur(individu l);
float obtenir_qualite(individu l);
individu initialiser_individu(individu i, int longIndiv);

#endif