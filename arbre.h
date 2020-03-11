#ifndef __ABR_H__
#define __ABR_H__

#include <stdio.h>

typedef int Element;

struct cellule {
    Element etiq;
    struct cellule *fd;
    struct cellule *fg;
};

typedef struct cellule *Arbre;

Arbre ArbreVide();

Arbre NouveauNoeud(Arbre g, Element c, Arbre d);

int EstVide(Arbre a);

Element Etiq(Arbre a);
 
Arbre FilsGauche(Arbre a);

Arbre FilsDroit(Arbre a);

void LibererArbre(Arbre a);

void EcrireArbre(FILE *fichier, Arbre a);

Arbre LireArbre(FILE *fichier);

void AfficherArbre(Arbre a);

#endif
