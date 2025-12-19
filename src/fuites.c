#include "../include/main.h"
#include "../include/fuites.h"
#include <string.h>

// Création d'un noeud d'AVL en prenant un identifiant et une adresse pour créer le glossaire
pGlossaire creerGlossaire(const char* id, Troncon* adresse){ 
    if (adresse == NULL || id == NULL){ 
        return NULL; // Si l'adresse ou l'identifiant est nul, il n'y a aucune raison de créer l'AVL
    }
    pGlossaire nouveau = malloc(sizeof(Glossaire)); 
    if (nouveau == NULL){
        printf("Erreur d'allocation de mémoire");
        exit(1); // Arrêt de la fonction en cas d'erreur d'allocation de mémoire
    }
    nouveau->id=strdup(id); // Copie de l'identifiant pris en paramètre dans la variable du nouveau noeud
    nouveau->adresse=adresse; 
    nouveau->fg=NULL; 
    nouveau->fd=NULL; 
    nouveau->eq=0; // Facteur d'équilibre initialisé à 0
    return nouveau;
}

pGlossaire Glossaire_rotationGauche(pGlossaire a){
    pGlossaire pivot = a->fd; // Le fils droit devient le pivot
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

pGlossaire Glossaire_rotationDroite(pGlossaire a){
 pGlossaire pivot = a->fg; // Le fils gauche devient le pivot
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
    if (strcmp(id, a->id) < 0){ // Cas où l'élément est plus petit
        a->fg=insertionGlossaire(a->fg, adresse, id, h); // Insertion dans le sous-arbre gauche 
        *h=-*h; // Inversion de l'impact de la hauteur
    }
    else if (strcmp(id, a->id) > 0){ // Cas où l'élément est plus grand
        a->fd=insertionGlossaire(a->fd, adresse, id, h); // Insertion dans le sous-arbre droit
    } else { // Elément déjà présent
        *h=0;
        return a;
    }
    if(*h != 0){ // Mis à jour du facteur d'équilibre
        a->eq += *h;
        a=equilibrerGlossaire(a); 
        if(a->eq == 0){ // Mis à jour de la hauteur
            *h=0;
        } else {
            *h=1;
        }
    }
    return a;
}

void libererGlossaire(pGlossaire a){ // Libération de l'avl glossaire
    if(a == NULL){
       return;
    }
    if(a->fd != NULL){
       libererGlossaire(a->fd); // Libération du sous-arbre droit
    }
    if(a->fg != NULL){
       libererGlossaire(a->fg); // Libération du sous-arbre gauche
    }
    free(a->id);
    free(a); // Libération du noeud courant
}

Troncon* rechercheGlossaire(pGlossaire a, const char* id) { // Recherche d'un identifiant dans le glossaire
    if (!a || !id){ // Cas où l'arbre est vide ou l'identifiant est nul
        return NULL;
    }
    int comparateur = strcmp(id,a->id); // Mis en place d'un comparateur lexicographique
    if (comparateur == 0){ // Cas où l'identifiant coïncide avec l'identifiant du noeud courant
        return a->adresse;
    }
    if (comparateur < 0){ // Cas où l'identifiant recherché est dans le sous-arbre gauche
        return rechercheGlossaire(a->fg,id);
    }
    else { // Cas où l'identifiant recherché est dans le sous-arbre droit
        return rechercheGlossaire(a->fd,id);
    }
    return NULL;
}

Troncon* creerTroncon(const char *id, double fuite, double volume){ // Création d'un tronçon dans le cas de l'arbre k-aire
    Troncon* nouveau = malloc(sizeof(Troncon));
    if (nouveau == NULL){
        printf("Erreur d'allocation de mémoire");
        exit(1);
    }
    nouveau->id = strdup(id);
    nouveau->fuite = fuite;
    nouveau->volume = volume;
    nouveau->nb_enfants = 0;
    nouveau->enfants = NULL;
    return nouveau;
}

void ajouter_enfant(Troncon* parent, Troncon* enfant){ // Ajout d'une infrastructure dans l'arbre k-aire
    Enfant* nv = malloc(sizeof(Enfant));
    if (nv == NULL){
        printf("Erreur d'allocation de mémoire");
        exit(1);
    }
    nv->noeud = enfant; // Association du tronçon enfant au noeud 
    nv->suivant = parent->enfants; // Insertion du noeud en tête de la liste chainée des enfants
    parent->enfants = nv;
    parent->nb_enfants ++; // Augmentation du nombre d'enfants suite à l'ajout
}

double propagation(Troncon* parent, double volume) {
    if (!parent || volume <= 0.0) return 0.0;

    // Perte locale
    double perte_locale = volume * (parent->fuite / 100.0);

    // Volume restant à distribuer aux enfants
    double volume_restant = volume - perte_locale;
    double total_fuite = perte_locale;

    // Si le tronçon a des enfants, distribuer le volume restant
    if (parent->nb_enfants > 0) {
        double part = volume_restant / parent->nb_enfants;
        Enfant* e = parent->enfants;
        while (e != NULL) {
            e->noeud->volume = part * (1.0 - e->noeud->fuite / 100.0); // Mise à jour du volume de l'enfant en fonction de sa fuite
            total_fuite += propagation(e->noeud, part);
        //printf("ID=%s vol=%lf leaks=%lf \n ", e->noeud->id, e->noeud->volume, e->noeud->fuite);

            e = e->suivant;
        }
    }

    return total_fuite;
}

double calcul_fuites(pGlossaire a, const char* id){
    if(a == NULL || id == NULL){ // Vérification des paramètres
        return -2.0;
    }
    Troncon* troncon = rechercheGlossaire(a, id); // Recherche de l'identifiant du tronçon dans le glossaire
    if (troncon == NULL){  
        return -1.0; // Renvoie -1 si le tronçon est nul
    } else {
        return propagation(troncon, troncon->volume); // Appel vers la fonction propagation en cas d'existence du tronçon
    }
}

void libererReseau(Troncon* troncon){ 
    if (troncon == NULL){ // Vérification du paramètre
        return;
    }
    Enfant* e = troncon->enfants; // Parcours et libération des enfants 
    while (e != NULL){
        Enfant* temp = e;
        libererReseau(e->noeud); // Libération récursive du sous-arbre
        e = e->suivant; // Passage à l'enfant suivant
        free(temp); // Libération de l'enfant
    }
    free(troncon->id); // Libération des champs
    free(troncon);
}

int traitement_ligne_fuite(
    const char* buffer,
    char* parent,
    char* enfant,
    char* service,
    double* valeur,
    double* fuite,
    double* somme
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
    //Vérif si source
    if (strcmp(parent,"-")==0 && strcmp(valeur_str, "-") !=0 && strcmp(fuite_str, "-") !=0) {
        if(somme) {
            double volume = atof(valeur_str);
            double fuite  = atof(fuite_str) / 100.0;

            *somme += volume * (1.0 - fuite);

        }
        
    }

    // Traitement du champ valeur
    if (strcmp(valeur_str, "-") == 0) {
        *valeur = 0.0;
    } else {
        *valeur = atof(valeur_str);
    }

    // Traitement du champ fuite
    if (strcmp(fuite_str, "-") == 0) {
        *fuite = 0.0;
    } else {
        *fuite = atof(fuite_str);
    }

    return 1;
}

