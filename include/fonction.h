#ifndef FONCTION_H
#define FONCTION_H
#include "main.h"
#include "histo.h"
#define MAX_CMP 5

void printErreur(const char *format);
int trieDict(const void* a, const void* b);
//void récupérer_max(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_max);
//void récupérer_max(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_max);
Dictionnaire* nUsinesOptimise(pAVL avl, int n, char *critere, int max, int *taille);
void remplirAVL(pAVL avl);
void lireFichier(const char* chemin_fichier, pAVL *avl);
void trim(char* str); // made by chatpgt
void ecrireUsine(Dictionnaire *dict, int taille, char destination[64], int type);
void jolieAffichage(Dictionnaire* dict, int type, int taile, char* critere);
void afficherDict(Dictionnaire* dict, int taille);
#endif