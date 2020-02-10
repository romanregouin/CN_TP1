#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//suppose que les proba donnée sont correcte et conforme au format attendu : 1 entier sur une ligne qui indique le nb de proba puis une proba en float
//sur chaque ligne avec des probas qui sont supposé correcte c-a-d somme des proba = 1 avec proba<1
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
    float somme = 0.00;
    float entropie = 0.00;
    printf("Voici vos probabilité : \n");
    for(int i=0;i<nb;i++){
        printf("%.2f | ",tab[i]);
        somme += tab[i]*log2f(tab[i]);
    }
    printf("\n");
    entropie = -somme;
    printf("Voici l'entropie : %.2f\n",entropie);

    return EXIT_SUCCESS;
}