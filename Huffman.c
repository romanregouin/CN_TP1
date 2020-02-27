#include <stdio.h>
#include <stdlib.h>

typedef struct noeud
{
    struct noeud *fgauche,*fdroite;
    int elem;
} noeud, *arbre;



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
    
}