#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    FILE *src;
    if(argc<2){
        printf("Syntaxe : %s [fichier contenant les proba]\n",argv[0]);
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
        if(res!=EOF){
            i++;
        }
    }
    if(i!=nb){
        printf("Nombre de symbole éroné\n");
        return EXIT_FAILURE;
    }
    printf("Voici vos probabilité : \n");
    for(int i=0;i<nb;i++){
        printf("%.2f | ",tab[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}