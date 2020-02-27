#include <stdio.h>
#include <stdlib.h>
#include "fap.h"
#include "arbrebin.h"


struct code_char {
    int lg;
    int code[50]; /* ne contient que des 0 ou des 1 */
};




/*
 
fap InitHuffman(TableOcc_t *TableOcc) {
    int min=1;
    int max=0;
    fap f=creer_fap_vide();
    for(int k=0;k<256;k++){
        if(max<TableOcc->tab[k])max=TableOcc->tab[k];
    }
    int max2;
    Arbre element;
    for(int i=0;min<=max;i++){
        max2=max;
        if(min==max)max--;
        for(int j=0;j<256;j++){
            if(min==TableOcc->tab[j]){
                element=NouveauNoeud(NULL,j,NULL);
                f=inserer(f,element,min);
            }
            if(min<TableOcc->tab[j] && max2>=TableOcc->tab[j])max2=TableOcc->tab[j];
        }
        min=max2;
    }
    return f;
}*/

fap InitHuffman(float* tab,int nb) {
    fap f=creer_fap_vide();
    Arbre element;
    for(int i=1;i<nb+1;i++){
        element=NouveauNoeud(NULL,i,NULL);
        f=inserer(f,element,tab[i-1]);
    }
    return f;
}





Arbre ConstruireArbre(fap file) {
    Arbre a;
    Arbre element1,element2;
    float priorite1,priorite2;
    if(est_fap_vide(file))return NULL;
    file =extraire(file,&element1,&priorite1);
    if(est_fap_vide(file))return element1;
    file =extraire(file,&element2,&priorite2);
    a=NouveauNoeud(element1,'\0',element2);
    while(!est_fap_vide(file)){
        file=inserer(file,a,priorite2+priorite1);
        file=extraire(file,&element1,&priorite1);
        file=extraire(file,&element2,&priorite2);
        a=NouveauNoeud(element1,'\0',element2);
    }
    
    return a;
}



void ParcoursArbre(Arbre huff,int pos,int* code,float* tab,struct code_char HuffmanCode[]){
    if(!EstVide(FilsGauche(huff))){
        code[pos]=0;
        ParcoursArbre(FilsGauche(huff),pos+1,code,tab,HuffmanCode);
    }if(!EstVide(FilsDroit(huff))){
        code[pos]=1;
        ParcoursArbre(FilsDroit(huff),pos+1,code,tab,HuffmanCode);
    }
    Element e=Etiq(huff);
    if(tab[e-1]>0 && pos!=0){
        HuffmanCode[e].lg=pos;
        for(int i=0;i<pos;i++){
            HuffmanCode[e].code[i]=code[i];
        }
    }
}


void ConstruireCode(Arbre huff,float* tab,struct code_char HuffmanCode[]){
    int code[256];
    if(huff!=NULL){
        if(EstVide(FilsGauche(huff)) && EstVide(FilsDroit(huff))){
            HuffmanCode[Etiq(huff)].lg=1;
            HuffmanCode[Etiq(huff)].code[0]=0;
        }else ParcoursArbre(huff,0,code,tab,HuffmanCode);
    }else printf("Fichier vide \n");
}

void AfficherCode(int nb,struct code_char HuffmanCode[]){
    for(int i=1;i<nb+1;i++){
        printf("Evenement %d: ",i);
        for(int j=0;j<HuffmanCode[i].lg;j++){
            printf("%d",HuffmanCode[i].code[j]);
        }
        printf("\n");
    }
}



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
    for(int i=0;i<nb;i++)tab[i]=0;
    res = fscanf(src,"%f",tab+i);
    while(res!=EOF){
        printf("%f \n",tab[i]);
        i++;
        res = fscanf(src,"%f",tab+i);
    }
    if(i!=nb){
        printf("Nombre de symbole éroné\n");
        printf("%d au lieu de %d \n",i,nb);
        return EXIT_FAILURE;
    }
    struct code_char HuffmanCode[50];
    fap f;
    Arbre a;
    f= InitHuffman(tab,nb);
    a=ConstruireArbre(f);
    ConstruireCode(a,tab,HuffmanCode);
    AfficherCode(nb,HuffmanCode);
    AfficherArbre(a);

    return EXIT_SUCCESS;
}