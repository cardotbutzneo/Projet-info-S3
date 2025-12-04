#ifndef AVL_H
#define AVL_H
#include "main.h"


/* typedef struct _noeud{
    int val;
}Noeud; 

typedef struct Usine {
    unsigned long identifiant;
    unsigned long capacite;
    unsigned long v_capte;
    unsigned long v_traite;
    struct Stockage* suivant_stockage;
} Usine; 


typedef struct Source {
    char *idsource;                 
    double volume;            
    float pourcentage_fuite;      
    struct Usine* suivant_usine;    
    //Pour les AVL
    //struct Source *gauche;
    //struct Source *droite;
} Source;

typedef struct Stockage {
    char *idusine;
    char* idstockage;                
    float pourcentage_fuite;     
    struct Jonction* suivant_jonction;  
    //struct Stockage *gauche;
    //struct Stockage *droite;
} Storage;
    
typedef struct Jonction {
    char* idstockage;                
    char* idjonction;
    float pourcentage_fuite;
    struct Raccordement* suivant_raccordement;
    //struct Jonction *gauche;
    //struct Jonction *droite;
}Jonction;

typedef struct Raccordement {
    char* idjonction;                
    char* idraccordement;
    float pourcentage_fuite;     
    struct Usager* suivant_raccordement;
    //struct Raccordement *gauche;
    //struct Raccordement *droite;
} Raccordement;

typedef struct Usager {
    char* idraccordement;                
    char* idusager;
    float pourcentage_fuite;
    char* idusine;
    //struct Usager *gauche;
    //struct Usager *droite;
} Usager;



    typedef struct Usine* pUsine;
    typedef struct Source* pSource;
    typedef struct Stockage* pStockage;
    typedef struct Jonction* pJonction;
    typedef struct Raccordement* pRaccordement;
    typedef struct Usager* pUsager;
*/



/*
typedef struct Usine {
    char* id;
    unsigned long capacite;
    unsigned long v_traite;
    unsigned long v_capte;
} Usine;

typedef struct Usine* pUsine;

typedef struct AVL {
    pUsine Usine;
    int eq;
    struct AVL* fd;
    struct AVL* fg;
} AVL;

typedef struct AVL* pAVL   */
#endif


