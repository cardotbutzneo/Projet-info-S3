#ifndef AVL_H
#define AVL_H
#include "main.h"

typedef struct Usine {
    char* id;
    unsigned long capacite;
    unsigned long v_traite;
    unsigned long v_capte;
} Usine;

typedef struct Usine* pUsine;

typedef struct AVL {
    pUsine Usine;
    int eq;
    struct AVL* fd;
    struct AVL* fg;
} AVL;

typedef struct AVL* pAVL   
#endif



