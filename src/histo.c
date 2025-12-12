#include "../include/main.h"
#include "../include/histo.h"
#include "../include/fonction.h"
#include <string.h>

char* extraireID(const char* texte) {
    const char* pos = strchr(texte, '#');
    if (!pos) return NULL;
    pos++; // après '#'

    const char* fin = pos;
    while (*fin && *fin != ' ' && *fin != ';' && *fin != '\n' && *fin != '\r') fin++;

    size_t taille = fin - pos;
    char* id = malloc(taille+1);
    memcpy(id, pos, taille);
    id[taille] = '\0';
    return id;
}


void recuperersource(char* sauvegarde[5], char* ligne) {
    char* temp = strdup(ligne);   // duplique la ligne pour que strtok puisse la modifier
    char* token = strtok(temp, ";");
    int i = 0;

    while (token && i < 5) {
        sauvegarde[i] = strdup(token);   // alloue et copie la chaîne
        token = strtok(NULL, ";");
        i++;
    }

    free(temp);
}
/* 
void verifMemoire(Token_liste* colonne){
    if (!colonne) return;
    Token_liste* temp = colonne;
    while (temp){
        if (!temp) libérer_token(colonne);
        exit(10);
    }
}
void _(Token_liste* colonne){
    verifMemoire(colonne);
    char* col1 = colonne->token;
    char* col2 = colonne->suivant->token;
    char* col3 = colonne->suivant->suivant->token;
    char* col4 = colonne->suivant->suivant->suivant->token;
    char* col5 = colonne->suivant->suivant->suivant->suivant->token;
}

pUsine creerUsine(Token_liste* liste){
    if (!liste) return NULL;
    pUsine usine = malloc(sizeof(Usine));
    if (!usine) exit(10);
    usine->capacite = liste->suivant->suivant->suivant->suivant->token;
    usine->id = liste->suivant->token;
    usine->v_capte = 0;
    usine->v_traite = 0;
    return usine;
}
*/
pAVL ajouterAVLUsine(pAVL avl,pUsine usine){
    int h=0;
    avl = insertionAVL(avl,usine,&h);
    return avl;
}
/*
int main() {
    char sauvegarde[64];   // un vrai buffer
    char ligne[] = "-;Source #HC900000Q;Unit #NM000000T;2956;0.915";  

    recuperersource(sauvegarde, ligne);
    printf("buffer : %s\n",sauvegarde);

    return 0;
}
*/

/*====================================
    Leaks
  ====================================
*/

//void lireDonneFuite(pAVL avl_usines, , char* source, )