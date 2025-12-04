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

typedef struct Usine* pUsine;

typedef struct AVL {
    pUsine usine;
    int eq;
    struct AVL* fd;
    struct AVL* fg;
} AVL;

typedef struct AVL* pAVL;   


#endif







