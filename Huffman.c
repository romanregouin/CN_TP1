#include <stdio.h>
#include <stdlib.h>
#include "fap.h"
#include "arbrebin.h"


struct code_char {
    int lg;
    int code[30]; /* ne contient que des 0 ou des 1 */
};


int power(int a,int n){
    if(n==1)return a;
    if(n==0)return 1;
    if(n%2==0)return power(a*a,n/2);
    else return a*power(a*a,(n-1)/2);
}




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

fap InitHuffman(float* tab,long int nb) {
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
    a=NouveauNoeud(element1,0,element2);
    while(!est_fap_vide(file)){
        file=inserer(file,a,priorite2+priorite1);
        file=extraire(file,&element1,&priorite1);
        file=extraire(file,&element2,&priorite2);
        a=NouveauNoeud(element1,0,element2);
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
    if(e>0 && tab[e-1]>0 && pos!=0){
        HuffmanCode[e].lg=pos;
        for(int i=0;i<pos;i++){
            HuffmanCode[e].code[i]=code[i];
        }
    }
}


void ConstruireCode(Arbre huff,float* tab,struct code_char HuffmanCode[]){
    int code[50];
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


/*
void AfficherCode_double(int nb,struct code_char HuffmanCode[]){
    for(int i=0;i<nb;i++){
        for(int j=0;j<nb;j++){
            printf("Evenement %d,%d: ",i+1,j+1);
            for(int h=0;h<HuffmanCode[1+i*nb+j].lg;h++){
                printf("%d",HuffmanCode[1+i*nb+j].code[h]);
            }
            printf("\n");
        }
    }
}
*/



void AfficherCode_n(int nb,int n,struct code_char HuffmanCode[]){
    for(int i=0;i<(power(nb,n));i++){
        printf("Evenement");
        for(int j=n-1;0<=j;j--){  
            int index=((i)/power(nb,j))%nb;  
            printf(" %d ",index+1);        
        }
        for(int h=0;h<HuffmanCode[1+i].lg;h++){
                printf("%d",HuffmanCode[1+i].code[h]);
            }
        printf("\n"); 
    }
}


float Longueur_moy(long int nb,struct code_char HuffmanCode[],float* tab,int m){
    float res=0;
    for(int i=1;i<nb+1;i++){
        res+=HuffmanCode[i].lg*tab[i-1];
    }
    printf("Longueur moyenne du code : %f \n",res);
    return res;
}


float* tab_mul(float* t,int m,int nb){
    int pow=power(nb,m);
    float* t3=malloc(sizeof(float)*pow);
    for(int i=0;i<pow;i++){
        t3[i]=1;
        float tmp;
        for(int j=0;j<m;j++){
            int index=((i)/power(nb,j))%nb;
            tmp=t[index];
            t3[i]*=tmp;
        }
    }
    return t3;
}



int main(int argc, char** argv){   
    FILE *src;
    if(argc<3){
        printf("Syntaxe : %s [fichier contenant les proba] [multiplicité des événements]\n",argv[0]);
        return EXIT_FAILURE;
    }
    src = fopen(argv[1],"r");
    if(src==NULL){
        printf("Erreur ouverture du fichier\n");
        return EXIT_FAILURE;
    }
    int m=atoi(argv[2]);
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
    
    fap f;
    Arbre a;
    long int nb3=power(nb,m);
    struct code_char HuffmanCode[nb3+1];
  
  
    /*
    f= InitHuffman(tab,nb);
    a=ConstruireArbre(f);
    ConstruireCode(a,tab,HuffmanCode);
    AfficherCode(nb,HuffmanCode);
    AfficherArbre(a);
    Longueur_moy(nb,HuffmanCode,tab,1);
    LibererArbre(a);
    */



   /*
    float tab2[nb*nb];

    for(int i=0;i<nb;i++){
        for(int j=0;j<nb;j++){
            tab2[i*nb+j]=tab[i]*tab[j];
        }
    }
    f= InitHuffman(tab2,nb*nb);
    a=ConstruireArbre(f);
    ConstruireCode(a,tab2,HuffmanCode);
    AfficherCode_double(nb,HuffmanCode);
    Longueur_moy(nb*nb,HuffmanCode,tab2,2);
    LibererArbre(a);
    */


    float* tab3=tab_mul(tab,m,nb);
    float res5=0;
    for(int i=0;i<power(nb,m);i++)res5+=tab3[i];
    
    f= InitHuffman(tab3,nb3);
    a=ConstruireArbre(f);
    ConstruireCode(a,tab3,HuffmanCode);
    AfficherCode_n(nb,m,HuffmanCode);
    Longueur_moy(nb3,HuffmanCode,tab3,m);
    
    LibererArbre(a);
    free(tab3);
    return EXIT_SUCCESS;
}