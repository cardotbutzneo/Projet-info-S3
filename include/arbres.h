#ifndef AVL_H
#define AVL_H
#include "main.h"

typedef struct{
    char* cle;
    unsigned long valeur;
}Dictionnaire;


typedef struct{
    char* id;
    unsigned long capacite;
    unsigned long v_traite;
    unsigned long v_capte;
} Usine;

typedef Usine* pUsine;

typedef struct _troncons{
    pUsine usine;
    char* id_amont;
    char *id_aval;
    double volume;
    float fuite;
}Troncons;

typedef struct AVL {
    pUsine usine;
    int eq;
    struct AVL* fd;
    struct AVL* fg;
} AVL;

typedef struct AVL* pAVL;   

//fonction

pAVL insertionAVL(pAVL a, pUsine usine, int *h);
void libererAVL(pAVL a);
int recherche_i(pAVL a, char* id);
pAVL recherche(pAVL a, char* id);
void afficherAVL(pAVL avl, int* cmp);
#endif