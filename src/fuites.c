#include "../include/main.h"
#include "../include/fuites.h"
#include <string.h>

// Création d'un noeud d'AVL en prenant un identifiant et une adresse pour créer le glossaire.
pGlossaire creerGlossaire(const char* id, Troncon* adresse){ 
    if (adresse == NULL || id == NULL){ 
        return NULL; // Si l'adresse ou l'identifiant est nul, il n'y a aucune raison de créer l'AVL.
    }
    pGlossaire nouveau = malloc(sizeof(Glossaire)); 
    if (nouveau == NULL){
        printf("Erreur d'allocation de mémoire");
        exit(1); // Arrêt de la fonction en cas d'erreur d'allocation de mémoire.
    }
    nouveau->id=strdup(id); // Copie de l'identifiant pris en paramètre dans la variable du nouveau noeud.
    nouveau->adresse=adresse; 
    nouveau->fg=NULL; 
    nouveau->fd=NULL; 
    nouveau->eq=0; // Facteur d'équilibre initialisé à 0.
    return nouveau;
}

pGlossaire Glossaire_rotationGauche(pGlossaire a){
    pGlossaire pivot = a->fd; // Le fils droit devient le pivot.
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
    return pivot; // Le pivot devient la nouvelle racine.
}

pGlossaire Glossaire_rotationDroite(pGlossaire a){
 pGlossaire pivot = a->fg; // Le fils gauche devient le pivot
 int eq_a = a->eq, eq_p = pivot->eq;
 a->fg = pivot->fd; // Le sous-arbre droit du pivot devient le fils gauche de 'a'
 pivot->fd = a; // 'a' devient le fils droit du pivot
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

 pGlossaire Glossaire_doubleRotationGauche(pGlossaire a){
   a->fd = Glossaire_rotationDroite(a->fd);
   return Glossaire_rotationGauche(a);
 }

pGlossaire Glossaire_doubleRotationDroite(pGlossaire a){
   a->fg = Glossaire_rotationGauche(a->fg);
   return Glossaire_rotationDroite(a);
 }

pGlossaire equilibrerGlossaire(pGlossaire a) {
    if (a->eq >= 2) { // Cas où le coté droit de l'arbre est déséquilibré.
        if (a->fd->eq >= 0) {
           return Glossaire_rotationGauche(a); 
        } else {
            return Glossaire_doubleRotationGauche(a); 
        }
    } else if (a->eq <= -2) { // Cas où le côté gauche de l'arbre est désiquilibré
        if (a->fg->eq <= 0) {
            return Glossaire_rotationDroite(a); 
        } else {
            return Glossaire_doubleRotationDroite(a);
        }
    }
    return a; // Aucun rééquilibrage nécessaire.
}

pGlossaire insertionGlossaire(pGlossaire a, Troncon* adresse, const char* id, int *h){ // Insertion d'un nouevau noeud dans l'AVL Glossaire
    if (a == NULL){ // Cas où l'arbre est vide 
        *h=1; // Augmentation de la hauteur suite à la création d'un nouveau noeud
        return creerGlossaire(id, adresse); 
    }
    if (strcmp(id, a->id) < 0){
        a->fg=insertionGlossaire(a->fg, adresse, id, h);
        *h=-*h;
    }
    else if (strcmp(id, a->id) > 0){
        a->fd=insertionGlossaire(a->fd, adresse, id, h);
    } else {
        *h=0;
        return a;
    }
    if(*h != 0){
        a->eq += *h;
        a=equilibrerGlossaire(a);
        if(a->eq == 0){
            *h=0;
        } else {
            *h=1;
        }
    }
    return a;
}

void libererGlossaire(pGlossaire a){
    if(a == NULL){
       return;
    }
    if(a->fd != NULL){
       libererGlossaire(a->fd);
    }
    if(a->fg != NULL){
       libererGlossaire(a->fg);
    }
    free(a->id);
    free(a); 
}

Troncon* rechercheGlossaire(pGlossaire a, const char* id) {
    if (!a || !id){
        return NULL;
    }
    int comparateur = strcmp(id,a->id);
    if (comparateur == 0){
        return a->adresse;
    }
    if (comparateur < 0){
        return rechercheGlossaire(a->fg,id);
    }
    else {
        return rechercheGlossaire(a->fd,id);
    }
    return NULL;
}

Troncon* creerTroncon(const char *id, double fuite){
    Troncon* nouveau = malloc(sizeof(Troncon));
    if (nouveau == NULL){
        printf("Erreur d'allocation de mémoire");
        exit(1);
    }
    nouveau->id = strdup(id);
    nouveau->fuite = fuite;
    nouveau->volume = 0.0;
    nouveau->nb_enfants = 0;
    nouveau->enfants = NULL;
    return nouveau;
}

void ajouter_enfant(Troncon* parent, Troncon* enfant){
    Enfant* nv = malloc(sizeof(Enfant));
    if (nv == NULL){
        printf("Erreur d'allocation de mémoire");
        exit(1);
    }
    nv->noeud = enfant;
    nv->suivant = parent->enfants;
    parent->enfants = nv;
    parent->nb_enfants ++;
}

double propagation (Troncon* parent, double Volume){
    if (parent == NULL){
        exit(1);
    }
    else{
        double perte_locale = Volume * (parent->fuite/100.0);
        double total_fuite = perte_locale;
        double volume_restant = Volume - perte_locale;
        if (parent->nb_enfants >0){
           double separation = volume_restant / parent->nb_enfants; 
            Enfant* e= parent->enfants;
            while (e != NULL){
            total_fuite +=propagation(e->noeud, separation);
            e = e->suivant;
            }
        }
        return total_fuite;
    }
}

double calcul_fuites(pGlossaire a, const char* id){
    if(a == NULL || id == NULL){
        return -2.0;
    }
    Troncon* troncon = rechercheGlossaire(a, id);
    if (troncon == NULL){
        return -1.0;
    } else {
        return propagation(troncon, troncon->volume);
    }
}

void libererReseau(Troncon* troncon){
    if (troncon == NULL){
        return;
    }
    Enfant* e = troncon->enfants;
    while (e != NULL){
        Enfant* temp = e;
        libererReseau(e->noeud);
        e = e->suivant;
        free(temp);
    }
    free(troncon->id);
    free(troncon);
}

int traitement_ligne_fuite(
    const char* buffer,
    char* parent,
    char* enfant,
    char* service,
    unsigned long* valeur,
    double* fuite
) {
    char valeur_str[64];
    char fuite_str[64];

    int nb = sscanf(buffer,
        "%63[^;];%63[^;];%63[^;];%63[^;];%63[^;\n]",
        parent, enfant, service, valeur_str, fuite_str
    );

    if (nb != 5) {
        return 0;
    }

    // Traitement du champ valeur
    if (strcmp(valeur_str, "-") == 0) {
        *valeur = 0;
    } else {
        *valeur = strtoul(valeur_str, NULL, 10);
    }

    // Traitement du champ fuite
    if (strcmp(fuite_str, "-") == 0) {
        *fuite = 0.0;
    } else {
        *fuite = atof(fuite_str);
    }

    return 1;
}
}
