#include "main.h"
#include "avl.h"

// pAVL creerAVL(pUsine Usine) {
//  if (usine == NULL){
//      return NULL;
//  }
//  pUsine nouveau = NULL; 
//  nouveau = malloc(sizeof(Usine));
//  if (nouveau == NULL){
//      printf("Erreur d'allocation de mémoire");
//      exit(1);
//  }
//  nouveau->usine=usine;
//  nouveau->fg=NULL;
//  nouveau->fd=NULL;
//  nouveau->eq=0;
// return nouveau;
// }

// pAVL rotationGauche(pAVL a){
// pAVL pivot = a->fd;
// int eq_a = a->eq, eq_p = pivot->eq;
// a->fd = pivot->fg;
// pivot->fg = a;
// if (eq_p>0) {
//    a->eq = eq_a-eq_p-1;
// } else {
//    a->eq = eq_a-0-1; 
// }
// int x = eq_a-2;
// int y = eq_a+eq_p-2;
// int z = eq_p-2;
// if (x <= y && x <= z){
//    eq_p = x;
// } else if (y <= x && y <= z) {
//    eq_p = y;
// } else if (z <= x && z <= y) {
//    eq_p = z;
// }
// return pivot;

// pAVL rotationDroite(pAVL a){
// pAVL pivot = a->fg;
// int eq_a = a->eq, eq_p = pivot->eq;
// a->fg = pivot->fd;
// pivot->fd = a;
// if (eq_p<0) {
//    a->eq = eq_a-eq_p+1;
// } else {
//    a->eq = eq_a-0+1; 
// }
// int x = eq_a-2;
// int y = eq_a+eq_p-2;
// int z = eq_p-2;
// if (x >= y && x >= z){
//    eq_p = x;
// } else if (y >= x && y >= z) {
//    eq_p = y;
// } else if (z >= x && z >= y) {
//    eq_p = z;
// }
// return pivot;

// pAVL doubleRotationGauche(pAVL a){
//   a->fd = rotationDroite(a->fd);
//   return rotationGauche(a);
// }

// pAVL doubleRotationDroite(pAVL a){
//   a->fg = rotationGauche(a->fg);
//   return rotationDroie(a);
// }

// pAVL equilibrerAVL(pAVL a) {
//    if (a->eq >= 2) {
//        if (a->fd->eq >= 0) {
//           return rotationGauche(a); 
//        } else {
//            return doubleRotationGauche(a); 
//        }
//    } else if (a->eq <= -2) {
//        if (a->fg->eq <= 0) {
//            return rotationDroite(a); 
//        } else {
//            return doubleRotationDroite(a);
//        }
//    }
//    return a; 
// }     

// void libererAVL(pAVL a){
//    if(a == NULL){
//       return;
//    }
//    if(a->fd != NULL){
//       libererAVL(a->fd);
//    }
//    if(a->fg != NULL){
//       libererAVL(a->fg);
//    }
//    free(avl->usine);
//    free(avl);
// }






