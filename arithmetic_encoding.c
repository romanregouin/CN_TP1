#include <stdlib.h>
#include <stdio.h>
#include "arithmetic_encoding.h"

int main(int argc, char** argv){
    int nb = atoi(argv[1]);
    int nb_letters = nb_diffrent_letters(nb,argv[2]);
    tabsymbole tab = create_table(nb, nb_letters,argv[2]);
    print_table(tab);
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
    tab.s = malloc(nb*sizeof(symbole));
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
            tab.s[num_letter].letter = letter;
            tab.s[num_letter].probability = (double)nb_occur/(double)nb;
            tab.s[num_letter].interval[0] = start_inter;
            tab.s[num_letter].interval[1] = start_inter + tab.s[num_letter].probability;

            start_inter = start_inter + tab.s[num_letter].probability;
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

double data_compression(char* msg, int nb){
    return 3.1;
}