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

    else if (strcmp(type_traitement,"leaks") == 0){

        printf("Traitement des leaks...\n");
        return 0;

    }
    return 0;
}