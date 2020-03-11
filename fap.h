#ifndef __FAP_H__
#define __FAP_H__

#include "arbre.h"

struct maillon;

typedef struct maillon *fap;

struct maillon {
    Arbre a;
    float priorite;
    fap prochain;
};

fap creer_fap_vide();

fap inserer(fap f, Arbre a, float priorite);

fap extraire(fap f, Arbre *a, float *priorite);

int est_fap_vide(fap f);

void detruire_fap(fap f);

#endif
