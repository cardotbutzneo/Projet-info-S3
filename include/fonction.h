#ifndef FONCTION_H
#define FONCTION_H
#include "main.h"
#include "histo.h"
#define MAX_CMP 5

void printErreur(const char *format);
void récupérer_max(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_max);
void récupérer_max(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_max);
void remplirAVL(pAVL avl);
void lireFichier(const char* chemin_fichier, pAVL *avl);
void trim(char* str); // made by chatpgt
#endif