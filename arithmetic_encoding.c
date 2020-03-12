#include <stdlib.h>
#include <stdio.h>
#include "arithmetic_encoding.h"

int main(int argc, char** argv){
    if(argc!=4){
        printf("Syntaxe : %s [nbletters] [message] [messageencoded]\n",argv[0]);
        return EXIT_FAILURE;
    }
    int nb = atoi(argv[1]);
    double tobedecoded = atof(argv[3]);
    int nb_letters = nb_diffrent_letters(nb,argv[2]);
    tabsymbole tab = create_table(nb, nb_letters,argv[2]);
    print_table(tab);
    double Vmsg = data_compression(argv[2],nb,tab);
    printf("La valeur du message comprésé est : %lf\n",Vmsg);
    char* msg = data_decompression(Vmsg,nb,tab);
    printf("Le message décodé est : %s\n",msg);
    char* msgdecoded = data_decompression(tobedecoded,nb,tab);
    printf("Le message %lf décodé est : %s\n",tobedecoded,msgdecoded);
    return EXIT_SUCCESS;
}

int nb_diffrent_letters(int nb, char* str){
    char know_letters[nb];
    int nb_know_letters=0;
    int finded = 0;
    for(int i=0;i<nb;i++){
        for(int j=0;j<nb_know_letters;j++){
            if(str[i]==know_letters[j]){
                finded = 1;
                j = nb_know_letters;
            }
        }
        if(finded==0){
            know_letters[nb_know_letters] = str[i];
            nb_know_letters++;
        }
        finded = 0;
    }
    return nb_know_letters;
}

int already_know(char letter, char* know_letters, int nb){
    for(int i=0;i<nb;i++){
        if(letter==know_letters[i]){
            return 1;
        }
    }
    return 0;
}

tabsymbole create_table(int nb, int nb_letters_diff, char* str){
    char know_letters[nb_letters_diff];
    int nb_konw_letters = 0;
    tabsymbole tab;
    tab.nb = nb_letters_diff;
    tab.s = malloc(nb_letters_diff*sizeof(symbole));
    double start_inter = 0;
    int i = 0;
    int num_letter = 0;
    while(num_letter<nb){
        char c = str[i];
        char letter = str[num_letter];
        if(!already_know(letter,know_letters,nb_konw_letters)){
            int nb_occur = 0;
            while(c!='\0'){
                if(c==letter){
                    nb_occur++;
                }
                i++;
                c = str[i];
            }
            tab.s[nb_konw_letters].letter = letter;
            tab.s[nb_konw_letters].probability = (double)nb_occur/(double)nb;
            tab.s[nb_konw_letters].interval[0] = start_inter;
            tab.s[nb_konw_letters].interval[1] = start_inter + tab.s[nb_konw_letters].probability;

            start_inter = start_inter + tab.s[nb_konw_letters].probability;
            num_letter++;
            i=0;
            nb_occur = 0;
            know_letters[nb_konw_letters] = letter;
            nb_konw_letters++;
        }else{
            num_letter++;
        }
    }
    return tab;
}

void print_table(tabsymbole tab){
    for(int i=0;i<tab.nb;i++){
        printf("%c : %lf [%lf,%lf]\n",tab.s[i].letter,tab.s[i].probability,tab.s[i].interval[0],tab.s[i].interval[1]);
    }
}

int find_pos_letter(tabsymbole tab, char letter){
    for(int i=0;i<tab.nb;i++){
        if(tab.s[i].letter==letter){
            return i;
        }
    }
    return -1;
}

double data_compression(char* msg, int nb, tabsymbole tab){
    int i=0;
    int indice;
    double Binf = 0;
    double Bsup = 1;
    double Vmsg = 1;
    double Vecart = Bsup - Binf;
    char letter = msg[i];
    for(int i=1;i<=nb;i++){
        indice = find_pos_letter(tab,letter);
        Bsup = Binf + Vecart * tab.s[indice].interval[1];
        Binf = Binf + Vecart * tab.s[indice].interval[0];
        Vmsg = (Bsup + Binf)/(double)2;
        Vecart = Bsup - Binf;
        letter = msg[i];
    }
    return Vmsg;
}

char find_letter(double V, tabsymbole tab){
    for(int i=0;i<tab.nb;i++){
        if((V>=tab.s[i].interval[0])&&(V<tab.s[i].interval[1])){
            return tab.s[i].letter;
        }
    }
    return 0;
}

char* data_decompression(double Vmsg, int nb, tabsymbole tab){
    char* msg = malloc(nb*sizeof(char));
    msg[0] = find_letter(Vmsg,tab);
    for(int i=1;i<nb;i++){
        int pos_letter = find_pos_letter(tab,msg[i-1]);
        Vmsg = (Vmsg - tab.s[pos_letter].interval[0])/tab.s[pos_letter].probability;
        msg[i] = find_letter(Vmsg,tab);
    }
    return msg;
}