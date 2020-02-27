typedef struct{
    char letter;
    double probability;
    double interval[2];
} symbole;

typedef struct{
    int nb;
    symbole* s;
} tabsymbole;

int nb_diffrent_letters(int nb, char* str);

int already_know(char letter, char* know_letters, int nb);

tabsymbole create_table(int nb, int nb_letters_diff, char* str);

void print_table(tabsymbole tab);

double data_compression(char* msg, int nb);