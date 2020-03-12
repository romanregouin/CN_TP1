#include "fap.h"
#include <stdlib.h>
#include <unistd.h>

fap creer_fap_vide() { return NULL; }

fap inserer(fap f, Arbre a, float priorite) {
    fap new, courant, precedent;

    new = (fap)malloc(sizeof(struct maillon));
    new->a = a;
    new->priorite = priorite;
    if ((f == NULL) || (priorite < f->priorite)) {
        new->prochain = f;
        f = new;
    }else {
        precedent = f;
        courant = f->prochain;
        while ((courant != NULL) && ( courant->priorite <= priorite )) {
            precedent = courant;
            courant = courant->prochain;
        }
        precedent->prochain = new;
        new->prochain = courant;
    }
    return f;
}

fap extraire(fap f, Arbre *a, float *priorite) {
    fap courant;
    if (f != NULL) {
        courant = f;
        *a = courant->a;
        *priorite = courant->priorite;
        f = courant->prochain;
        free(courant);
    }
    return f;
}

int est_fap_vide(fap f) {
     return f == NULL; 
}

void detruire_fap(fap f) {
    Arbre a;
    float priorite;
    while (!est_fap_vide(f))f = extraire(f, &a, &priorite);
}
