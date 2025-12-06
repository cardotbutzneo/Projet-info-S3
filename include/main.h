#ifndef MAIN_H
#define MAIN_H
// include librairie de base
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// include librairie perso
#include "arbres.h"
#include "fonction.h"
#include "histo.h"

//constante
#define MAX_CMP 5

// structures

// fonctions
Token_liste* ouvrir_fichier(const char* nom_fichier);
void libérer_token(Token_liste* liste);

#endif
