#include "main.h"

Critere critere_trie_global = MAX;  

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage : ./main <critere de trie>\n");
        return 1;
    }
    char* type_traitement = argv[1];

    if (strcmp(type_traitement,"histo") == 0){

        char* critere = argv[2];
        if (strcmp(critere, "src") != 0 &&
            strcmp(critere, "real") != 0 &&
            strcmp(critere, "max") != 0 &&
            strcmp(critere, "all") != 0) {
            fprintf(stderr, "Critère invalide : %s\n", critere);
            return 1;
        }

        // --------------------------------------------------------
        // Lecture et remplissage de l'AVL
        pAVL avl = NULL;
        printf("Lecture en cours...\n");
        lireFichier(&avl);
        if (!avl) {
            fprintf(stderr, "Erreur lors de la lecture du fichier.\n");
            return 1;
        }
        printf("Lecture réussie\n");

        remplirAVL(&avl);
        printf("Remplissage réussi\n");

        // --------------------------------------------------------
        // Détermination du critère de tri

        if (strcmp(critere, "max") == 0 || strcmp(critere,"all") == 0) {
            critere_trie_global = MAX;
            critere = "max";
        } else if (strcmp(critere, "src") == 0) {
            critere_trie_global = SRC;
        } else if (strcmp(critere, "real") == 0) {
            critere_trie_global = REAL;
        }
        // --------------------------------------------------------
        // Récupération des meilleures et pires usines
        int taille_m = 0, taille_p = 0;
        int n_max = 10;
        int n_min = 50;

        pUsine* n_meilleurs = nUsinesOptimise(avl, n_max, critere, 1, &taille_m);
        pUsine* n_pire = nUsinesOptimise(avl, n_min, critere, 0, &taille_p);

        if (!n_meilleurs || !n_pire) {
            fprintf(stderr, "Erreur lors de la récupération des usines optimisées.\n");
            libererAVL(avl);
            return 1;
        }

        // --------------------------------------------------------
        // Tri des tableaux
        //qsort(n_meilleurs, taille_m, sizeof(Usine*), trieDict);
        //qsort(n_pire, taille_p, sizeof(Usine*), trieDict);

        // --------------------------------------------------------
        // Écriture dans les fichiers
        char chemin[64] = "";
        ecrireUsine(n_meilleurs, taille_m, chemin, 1);
        chemin[0] = '\0';
        ecrireUsine(n_pire, taille_p, chemin, 0);

        // --------------------------------------------------------
        // Libération mémoire
        free(n_meilleurs);
        free(n_pire);
        libererAVL(avl);
        printf(ROUGE"Mémoire libérée\n"RESET);

        // --------------------------------------------------------
    }
    // Gestion des fuites
    else if (strcmp(type_traitement, "leaks") == 0) {
        printf("Traitement des leaks '%s'...\n", argv[2]);
        char* id_usine = argv[2];
        pGlossaire glossaire = NULL;
        int h = 0;
        char buffer[1024];
        char dash[8];
        char parent_name[64];
        char enfant_name[64];
        double somme = 0.0;
        double valeur;
        double fuite=0.0;

        while (fgets(buffer, sizeof(buffer), stdin)) {

            if (traitement_ligne_fuite(buffer, dash, parent_name, enfant_name, &valeur, &fuite,&somme)) {
                Troncon* parent_tr = NULL;
                Troncon* enfant_tr = NULL;
                
                // --- Traitement du parent ---
                if (strcmp(parent_name, "-") != 0) {

                    parent_tr = rechercheGlossaire(glossaire, parent_name);

                    if (!parent_tr) { //Vérifie si le tronçon parent n’existe pas encore dans le glossaire.
                            parent_tr = creerTroncon(parent_name, fuite, valeur); // avc valeur le volume réel du tronçon
                        } else if (valeur > 0) { //Ce bloc est exécuté si le parent existe déjà dans le glossaire, pas de comportement indéfini grâce au creerTroncon juste avant,si on mettait à jour à chaque ligne,on risque d'écraser le volume du parent par 0 c’est ce qui faisait que tt les volumes étaient nuls à un moment
                            parent_tr->volume = valeur;
                            parent_tr->fuite = fuite;
                        }
                    glossaire = insertionGlossaire(glossaire, parent_tr, parent_name, &h);
                }

                // --- Traitement de l’enfant ---
                if (strcmp(enfant_name, "-") != 0) {

                    enfant_tr = rechercheGlossaire(glossaire, enfant_name);

                                    if (!enfant_tr) {
                        enfant_tr = creerTroncon(enfant_name, fuite, valeur);
                    } else if (valeur > 0) {
                        enfant_tr->volume = valeur;
                        enfant_tr->fuite = fuite;
                    }

                    glossaire = insertionGlossaire(glossaire, enfant_tr, enfant_name, &h);
                }

                if (parent_tr && enfant_tr) { // Vérifie doublon
                    
                    int exists = 0;
                    for (Enfant* e = parent_tr->enfants; e; e = e->suivant) {
                        if (e->noeud == enfant_tr) { exists = 1; break; }
                    }
                    if (!exists) ajouter_enfant(parent_tr, enfant_tr);
                }

            } else {
                fprintf(stderr, "Ligne mal formée : %s", buffer);
            }
        }

        Troncon* usine = rechercheGlossaire(glossaire, id_usine);
        if (!usine) {
            fprintf(stderr, "Usine non trouvée : %s\n", id_usine);
        } 

        else {
            usine->volume=somme;
            double total_fuites = calcul_fuites(glossaire, id_usine);   
            int verif = ecriture_fichier(id_usine, total_fuites); 
            if (verif ==3){
                fprintf(stderr, "Fichier vide \n");
            }
        }
        libererGlossaire(glossaire);
        libererReseau(usine);
    }
    
    return 0;
}
