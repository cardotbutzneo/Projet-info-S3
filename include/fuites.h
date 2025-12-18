#ifndef FUITES_H
#define FUITES_H
// Arbre K-aire
typedef struct enfant { // Liste chaînée permettant à un tronçon d’avoir un nombre d’enfants non connu à l’avance.
    struct Troncon* noeud; // Pointeur vers le tronçon enfant (en aval)
    struct enfant* suivant;
} Enfant;

typedef struct Troncon {
    char *id;
    double volume;
    double fuite;
    int nb_enfants;
    Enfant *enfants; // Liste chaînée des tronçons enfants
} Troncon;

// Glossaire
typedef struct Glossaire {
    char *id;
    Troncon* adresse;
    int eq; // Facteur d'équilibre
    struct Glossaire* fd; // Pointeur vers le fils gauche
    struct Glossaire* fg; // Pointeur vers le fils droit
} Glossaire;

typedef struct Glossaire* pGlossaire;
pGlossaire creerGlossaire(const char* id, Troncon* adresse);
pGlossaire Glossaire_rotationGauche(pGlossaire a);
pGlossaire Glossaire_rotationDroite(pGlossaire a);
pGlossaire Glossaire_doubleRotationGauche(pGlossaire a);
pGlossaire Glossaire_doubleRotationDroite(pGlossaire a);
pGlossaire equilibrerGlossaire(pGlossaire a);
pGlossaire insertionGlossaire(pGlossaire a, Troncon* adresse, const char* id, int *h);
void libererGlossaire(pGlossaire a);
Troncon* rechercheGlossaire(pGlossaire a, const char* id);
Troncon* creerTroncon(const char *id, double fuite, double volume);
void ajouter_enfant(Troncon* parent, Troncon* enfant);
double propagation (Troncon* parent, double Volume);
double calcul_fuites(pGlossaire a, const char* id);
void libererReseau(Troncon* troncon);
int traitement_ligne_fuite(const char* buffer,char* parent, char* enfant, char* dash, double* valeur, double* fuite, double* somme);


#endif
