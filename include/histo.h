#ifndef HISTO_H
#define HISTO_H

#include "main.h"
/*
typedef struct {
    char* id;
}
*/
void recuperersource(char* sauvegarde[5], char* ligne);
pAVL ajouterAVLUsine(pAVL avl,pUsine usine);
char* extraireID(const char* token);

#endif