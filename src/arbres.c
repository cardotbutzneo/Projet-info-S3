#include "main.h"
#include "arbres.h"
#include <string.h>
pAVL creerAVL(pUsine usine) {
  if (usine == NULL){
      return NULL;
  }
  pAVL nouveau = NULL; 
  nouveau = malloc(sizeof(Usine));
  if (nouveau == NULL){
      printf("Erreur d'allocation de mémoire");
      exit(1);
  }
  nouveau->usine=usine;
  nouveau->fg=NULL;
  nouveau->fd=NULL;
  nouveau->eq=0;
 return nouveau;
}

pAVL rotationGauche(pAVL a){
 pAVL pivot = a->fd;
 int eq_a = a->eq, eq_p = pivot->eq;
 a->fd = pivot->fg;
 pivot->fg = a;
 if (eq_p>0) {
    a->eq = eq_a-eq_p-1;
 } else {
    a->eq = eq_a-0-1; 
 }
 int x = eq_a-2;
 int y = eq_a+eq_p-2;
 int z = eq_p-2;
 if (x <= y && x <= z){
    eq_p = x;
 } else if (y <= x && y <= z) {
   eq_p = y;
 } else if (z <= x && z <= y) {
    eq_p = z;
 }
 return pivot;
}

pAVL rotationDroite(pAVL a){
 pAVL pivot = a->fg;
 int eq_a = a->eq, eq_p = pivot->eq;
 a->fg = pivot->fd;
 pivot->fd = a;
 if (eq_p<0) {
   a->eq = eq_a-eq_p+1;
 } else {
    a->eq = eq_a-0+1; 
 }
 int x = eq_a-2;
 int y = eq_a+eq_p-2;
 int z = eq_p-2;
 if (x >= y && x >= z){
    eq_p = x;
 } else if (y >= x && y >= z) {
    eq_p = y;
 } else if (z >= x && z >= y) {
    eq_p = z;
 }
 return pivot;
}
 pAVL doubleRotationGauche(pAVL a){
   a->fd = rotationDroite(a->fd);
   return rotationGauche(a);
 }

pAVL doubleRotationDroite(pAVL a){
   a->fg = rotationGauche(a->fg);
   return rotationDroite(a);
 }

pAVL equilibrerAVL(pAVL a) {
    if (a->eq >= 2) {
        if (a->fd->eq >= 0) {
           return rotationGauche(a); 
        } else {
            return doubleRotationGauche(a); 
        }
    } else if (a->eq <= -2) {
        if (a->fg->eq <= 0) {
            return rotationDroite(a); 
        } else {
            return doubleRotationDroite(a);
        }
    }
    return a; 
}     

void libererAVL(pAVL a){
    if(a == NULL){
       return;
    }
    if(a->fd != NULL){
       libererAVL(a->fd);
    }
    if(a->fg != NULL){
       libererAVL(a->fg);
    }
    free(a->usine);
    free(a); 
}
/*
void parcoursAVL(pAVL a){
   if(a == NULL){
      return;
   }
   printf("%s - Max : %lu; - Src : %u; - Real : %lu", a->usine->id; a->usine->capacite, a->usine->v_capte, a->usine->v_traite);
   parcoursAVL(a->fd);
   parcoursAVL(a->fg);
}
*/

int hauteur(pAVL a){
   if (a == NULL){
      return 0;
   }
   int hd = hauteur(a->fd);
   int hg = hauteur(a->fg);
   if(hd > hg){
      return 1+hd;
   } else {
      return 1+hg;
   }
}

int recherche_i(pAVL a, char* id){
    if(a == NULL){
        return 0;
    }
    trim(id);
    trim(a->usine->id);
    printf("id '%s' usine vs id '%s'\n",a->usine->id,id);
    int comparateur=strcmp(id, a->usine->id);
    if(comparateur < 0){
        return recherche_i(a->fg, id);
    } 
    if(comparateur == 0){
        return 1;
    }
    else {
        return recherche_i(a->fd, id);
    }
}

pAVL recherche(pAVL a, char* id) {
    if (!a || !id) return NULL;

    // Nettoyer les deux chaînes
    trim(id);
    trim(a->usine->id);

    int cmp = strcmp(id, a->usine->id);

    if (cmp == 0) return a;
    else if (cmp < 0) return recherche(a->fg, id);
    else return recherche(a->fd, id);
}

pAVL insertionAVL(pAVL a, pUsine usine, int *h){
    if (a == NULL){
        *h=1;
        return creerAVL(usine);
    }
    else if (strcmp(a->usine->id, usine->id) < 0){
        a->fg=insertionAVL(a->fg, usine, h);
        *h=-*h;
    }
    else if (strcmp(a->usine->id, usine->id) > 0){
        a->fd=insertionAVL(a->fd, usine, h);
    } else {
        *h=0;
        return a;
    }
    if(*h != 0){
        a->eq += *h;
        a=equilibrerAVL(a);
        if(a->eq == 0){
            *h=0;
        } else {
            *h=1;
        }
    }
    return a;
}

void afficherAVL(pAVL avl, int* cmp){
    if (!avl) return;
    afficherAVL(avl->fg,cmp);
    printf("====================\n");
    if (cmp) printf("\033[31mNoeud n°%d\033[0m\n",*cmp);
    printf("Id : %s\n",avl->usine->id);
    printf("Capacité : %lu\n",avl->usine->capacite);
    printf("Volume capté : %lu\n",avl->usine->v_capte);
    printf("Volume traité : %lu\n",avl->usine->v_traite);
    *cmp += 1;
    afficherAVL(avl->fd,cmp);
}