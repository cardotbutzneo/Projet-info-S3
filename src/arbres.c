#include "main.h"
#include "arbres.h"
#include "couleurs.h"
#include <string.h>
pAVL creerAVL(pUsine usine) { // Création d'un noeud d'AVL en prenant une usune en paramètre
  if (usine == NULL){
      return NULL; // Si l'usine est égale à NULL, il n'y a aucune raison de créer l'AVL
  }
  pAVL nouveau = NULL; 
  nouveau = malloc(sizeof(Usine));
  if (nouveau == NULL){
      printf("Erreur d'allocation de mémoire");
      exit(1); // Arrêt de la fonction en cas d'erreur d'allocation de mémoire
  }
  nouveau->usine=usine; // Mis à jour des champs 
  nouveau->fg=NULL;
  nouveau->fd=NULL;
  nouveau->eq=0; // Facteur d'équilibre initialisé à 0
 return nouveau;
}

pAVL rotationGauche(pAVL a){
 pAVL pivot = a->fd; // Le fils droit devient le pivot 
 int eq_a = a->eq, eq_p = pivot->eq;
 a->fd = pivot->fg; // Le sous-arbre gauche du pivot devient le fils droit de 'a'
 pivot->fg = a; // 'a' devient le fils gauche du pivot
 if (eq_p>0) { // Mise à jour des facteurs d'équilibre
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
 return pivot; // Le pivot devient la nouvelle racine
}

pAVL rotationDroite(pAVL a){
 pAVL pivot = a->fg; // Le fils gauche devient le pivot
 int eq_a = a->eq, eq_p = pivot->eq;
 a->fg = pivot->fd; // Le sous-arbre droit du pivot devient le fils gauche de 'a'
 pivot->fd = a; // 'a' devient le fils droit du pivot
 if (eq_p<0) { // Mis à jour des facteurs d'équilibre
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
 return pivot; // Le pivot devient la nouvelle racine
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
    if (a->eq >= 2) { // Cas où le coté droit de l'arbre est déséquilibré
        if (a->fd->eq >= 0) {
           return rotationGauche(a); 
        } else {
            return doubleRotationGauche(a); 
        }
    } else if (a->eq <= -2) { // Cas où le côté gauche de l'arbre est désiquilibré
        if (a->fg->eq <= 0) {
            return rotationDroite(a); 
        } else {
            return doubleRotationDroite(a);
        }
    }
    return a; // Aucun rééquilibrage nécessaire
}     

void libererAVL(pAVL a){ // Libération de l'AVL
    if(a == NULL){
       return;
    }
    if(a->fd != NULL){
       libererAVL(a->fd); // Libération du sous-arbre droit
    }
    if(a->fg != NULL){
       libererAVL(a->fg); // Libération du sous-arbre gauche
    }
    free(a->usine);
    free(a); // Libération du noeud courant
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
   if (a == NULL){ // Cas où l'arbre est vide
      return 0; // Hauteur nulle 
   }
   int hd = hauteur(a->fd); // Calcul récursif de la hauteur du sous-arbre droit
   int hg = hauteur(a->fg); // Calcul récursif de la hauteur du sous-arbre gauche
   if(hd > hg){ // La hauteur est le maximum des deux hauteurs
      return 1+hd;
   } else {
      return 1+hg;
   }
}

int recherche_i(pAVL avl, char* id){
    if (!avl || !id){
        printf("pointeur NULL\n");
        return 0;
    }
    int comparaison = strcmp(avl->usine->id,id); // ligne de mort
    //printf(" id lu : '%s' vs '%s'\n",id,avl->usine->id);
    //if (avl->fg) printf("id du fils gauche : '%s'\n",avl->fg->usine->id);
    //if (avl->fd) printf("id du fils droit : '%s'\n",avl->fd->usine->id);
    //printf("c : %d\n",comparaison);
    if (comparaison == 0) return 1;
    if (comparaison > 0) return recherche_i(avl->fg,id);
    else return recherche_i(avl->fd,id);
    return -1;
}

pAVL recherche(pAVL a, const char* id) {
    if (!a || !id){
        //printf("Erreur\n");
        return NULL;
    }
    int comparateur = strcmp(id,a->usine->id);
    //printf(" id lu : '%s' vs '%s'\n",a->usine->id,id);
    //if (a->fg) printf("id du fils gauche : '%s'\n",a->fg->usine->id);
    //if (a->fd) printf("id du fils droit : '%s'\n",a->fd->usine->id);
    //printf("c : %d\n",comparateur);
    if (comparateur == 0) return a;
    if (comparateur < 0) return recherche(a->fg,id);
    else return recherche(a->fd,id);
    return NULL;
}


pAVL insertionAVL(pAVL a, pUsine usine, int *h){
    if (a == NULL){ // Cas où l'arbre est vide
        *h=1; // Augmentation de la hauteur suite à la création d'un nouveau noeud
        return creerAVL(usine);
    }
    if (strcmp(usine->id, a->usine->id) < 0){ // Cas où l'élément est plus petit
        a->fg=insertionAVL(a->fg, usine, h); // Insertion dans le sous-arbre gauche
        *h=-*h; // Inversion de l'impact de la hauteur
    }
    else if (strcmp(usine->id, a->usine->id) > 0){ // Cas où l'élément est plus grand
        a->fd=insertionAVL(a->fd, usine, h); // Insertion dans le sous-arbre droit
    } else { // Elément déjà présent
        *h=0;
        return a;
    }
    if(*h != 0){ // Mis à jour du facteur d'équilibre
        a->eq += *h;
        a=equilibrerAVL(a);
        if(a->eq == 0){ // Mis à jour de la hauteur
            *h=0;
        } else {
            *h=1;
        }
    }
    return a;
}

void afficherAVL(pAVL avl, int *cmp){
    if (!avl) return;

    afficherAVL(avl->fg, cmp);
    printf("==========================\n");

    if (cmp) {
        printf(ROUGE"Noeud n°%d\033[0m\n"RESET, *cmp);
        (*cmp)++;
    }
    printf("Id                                 : '%s'\n", avl->usine->id);
    printf("Capactité max de traitement        : %.3e m³\n",(double)avl->usine->capacite);
    printf("Volume capté                       : %.3e m³\n", (double)avl->usine->v_capte);
    printf("Volume traité                      : %.3e m³\n", (double)avl->usine->v_traite);

    afficherAVL(avl->fd, cmp);
}

