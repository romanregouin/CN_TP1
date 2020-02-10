#include <stdio.h>
#include <stdlib.h>

typedef struct noeud
{
    struct noeud *fgauche;
    struct noeud *fdroite;
    int elem;
} *arbre;



typedef struct {
    int** code;
} huffman;

int main(int argc, char** argv){   
    FILE *src;
    if(argc<2){
        printf("Syntaxe : ./%s [fichier contenant les proba]\n",argv[0]);
        return EXIT_FAILURE;
    }
    src = fopen(argv[1],"r");
    if(src==NULL){
        printf("Erreur ouverture du fichier\n");
        return EXIT_FAILURE;
    }
    int nb;
    int res;
    int i =0;
    res = fscanf(src,"%d",&nb);
    if(res!=1){
        printf("ERREUR\n");
        return EXIT_FAILURE;
    }
    float tab[nb];
    while(res!=EOF){
        res = fscanf(src,"%f",&tab[i]);
        i++;
    }
    if(i!=nb){
        printf("Nombre de symbole éroné\n");
        return EXIT_FAILURE;
    }
    float tab2[nb];
    float tmp=0;
    int nb2=0;
    arbre a;
    float min1=-1,min2=-2;
    arbre* tab3[nb];
    a=malloc(sizeof(struct noeud));
    a->fgauche=malloc(sizeof(struct noeud));
    a->fdroite=malloc(sizeof(struct noeud));
    nb--;
    tmp=tab[nb];
    a->fgauche->elem=tab[nb];
    a->fgauche->fgauche=NULL;
    a->fgauche->fdroite=NULL;
    nb--;
    tmp+=tab[nb];
    a->fdroite->elem=tab[nb];
    a->fdroite->fgauche=NULL;
    a->fdroite->fdroite=NULL;
    tab2[nb2]=tmp;
    tab3[nb2]=a;
    while(nb>0){

    }


    free(tab);
    free(tab2);
}