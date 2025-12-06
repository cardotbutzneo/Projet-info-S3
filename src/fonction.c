#include "main.h"
#include "arbres.h"
#include "histo.h"
#include <string.h>

void printErrreur(char *format){
    if (!format) return;
    fprintf(stderr,format);
}

void récupérer_max(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_max) { // récupère le max dans l'ABR par un parcourt infix inverse
    if (!avl || !dict || !cmp_max || *cmp_max >= MAX_CMP) {
        return; 
    }

    récupérer_max(avl->fd, dict, cmp_max);

    if (*cmp_max < MAX_CMP) {
        dict[*cmp_max].cle = avl->usine->id;
        dict[*cmp_max].valeur = avl->usine->v_traite;
        (*cmp_max)++;
    }
    récupérer_max(avl->fg, dict, cmp_max);
}

void récupérer_min(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_min) { // récupère le min dans l'ABR par un parcourt infix 
    if (!avl || !dict || !cmp_min || *cmp_min >= MAX_CMP) {
        return; 
    }
    récupérer_min(avl,dict,cmp_min);

    if (*cmp_min < MAX_CMP) {
        dict[*cmp_min].cle = avl->usine->id;
        dict[*cmp_min].valeur = avl->usine->v_traite;
        (*cmp_min)++;
    }
    récupérer_min(avl->fd, dict, cmp_min);
}

Token_liste* creerToken(const char* valeur){
    if (!valeur) return NULL;

    Token_liste* nouveau = malloc(sizeof(Token_liste));
    if (!nouveau) return NULL;
    nouveau->suivant = NULL;
    strncpy(nouveau->token, valeur, sizeof(nouveau->token));
    nouveau->token[sizeof(nouveau->token)-1] = '\0';
    return nouveau;
}


Token_liste* ouvrir_fichier(const char* nom_fichier){
    char chemin[256];
    snprintf(chemin, sizeof(chemin), "gnuplot/data/%s.dat", nom_fichier);

    FILE *f = fopen(chemin, "r");
    if (!f) {
        printErrreur("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }

    char buffer[256];
    Token_liste* liste = NULL;
    Token_liste* courant = NULL;

    while (fgets(buffer, sizeof(buffer), f)) {

        // enlever le \n
        buffer[strcspn(buffer, "\n")] = '\0';

        Token_liste* nouveau = creerToken(buffer);

        if (!liste) {
            liste = nouveau;
            courant = liste;
        } else {
            courant->suivant = nouveau;
            courant = nouveau;
        }
    }

    fclose(f);
    return liste;
}

void libérer_token(Token_liste* liste){
    while (liste){
        Token_liste* f = liste;
        liste = liste->suivant;
        free(f);
    }
}