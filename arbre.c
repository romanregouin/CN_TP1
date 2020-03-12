#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>


Arbre ArbreVide() { return NULL; }

Arbre NouveauNoeud(Arbre g, Element c, Arbre d) {
    Arbre a = (Arbre)malloc(sizeof(struct cellule));

    a->etiq = c;
    a->fg = g;
    a->fd = d;

    return a;
}


int EstVide(Arbre a) { return (a == NULL); }



Element Etiq(Arbre a) { return a->etiq; }





Arbre FilsGauche(Arbre a) { return a->fg; }




Arbre FilsDroit(Arbre a) { return a->fd; }



void LibererArbre(Arbre a) {
    if (!EstVide(a)) {
        LibererArbre(FilsGauche(a));
        LibererArbre(FilsDroit(a));
        free(a);
    }
}





int cpt_noeud;

int EcrireArbreRec(FILE *fichier, Arbre a) {
    int fg, fd;
    int racine;

    if (EstVide(a)) {
        /* Ne rien ecrire, renvoyer 0 */
        return 0;
    } else {
        /* Ecrire le fils gauche, fg = caractere a la racine du fils gauche */
        fg = EcrireArbreRec(fichier, FilsGauche(a));
        /* Ecrire le fils droit, fd = caractere a la racine du fils droit */
        fd = EcrireArbreRec(fichier, FilsDroit(a));
        /* Ecrire la sequence (caractere du noeud courant, fg, fd) */
        if (fg == 0) {
            /* Ecriture d'une feuille : le code de l'arbre est le code
               ascii du caractere */
            racine = (int)Etiq(a);
        } else {
            racine = cpt_noeud;
            cpt_noeud += 1;
        };
        fwrite(&racine, sizeof(int), 1, fichier);
        fwrite(&fg, sizeof(int), 1, fichier);
        fwrite(&fd, sizeof(int), 1, fichier);
        return racine;
    }
}

void EcrireArbre(FILE *fichier, Arbre a) {
    int zero = 0;
    cpt_noeud = 256;
    EcrireArbreRec(fichier, a);
    fwrite(&zero, sizeof(int), 1, fichier);
}


Arbre LireArbre(FILE *fichier) {
    Arbre TabArbre[512];
    int lu, fg, fd, racine;
    Element etiq;
    TabArbre[0] = ArbreVide();
    racine = 0;
    fread(&lu, sizeof(int), 1, fichier);
    while (lu != 0) {
        fread(&fg, sizeof(int), 1, fichier);
        fread(&fd, sizeof(int), 1, fichier);
        if (fg == 0) {
            etiq = (Element)lu;
        } else {
            etiq = 'a';
        }
        TabArbre[lu] = NouveauNoeud(TabArbre[fg], etiq, TabArbre[fd]);
        racine = lu;
        fread(&lu, sizeof(int), 1, fichier);
    }
    return TabArbre[racine];
}

void AfficherArbreRec(Arbre a, int indent) {
    int i;
    if (!EstVide(a)) {
        for (i = 0; i < indent; i++) {
            printf(" ");
        }
        printf("%d\n", Etiq(a));
        AfficherArbreRec(FilsGauche(a), indent + 2);
        AfficherArbreRec(FilsDroit(a), indent + 2);
    }
}

void AfficherArbre(Arbre a) { AfficherArbreRec(a, 0); }
