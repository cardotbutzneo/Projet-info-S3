#include "main.h"
int main(int argc, char* argsv[])
{
    if (argc != 2){
        printf("Usage : ./main <critere de trie>\n");
        return 1;
    }
    char* critere = argsv[1];
      if (strcmp(critere, "v_traite") != 0 &&
        strcmp(critere, "v_capte") != 0 &&
        strcmp(critere, "capacite") != 0) {
        fprintf(stderr, "Critère invalide : %s\n", critere);
        return 1;
    }
    pAVL avl = NULL;
    printf("Lecture en cours...\n");
    lireFichier("usine",&avl); // lit tout le fichier des sources et l'ajoute à l'avl
    if (avl) printf("lecture réussie\n");
    //printf("Affichage avant remplissage\n");
    //afficherAVL(avl,NULL);
    //printf("lecture ptr avl : '%s' \n",avl->usine->id);
    //printf("id : %s\n",avl->usine->id);
    remplirAVL(avl);
    /*
    int n = recherche_i(avl,"CE100000E");
    printf("====================\n");
    if (n == 1) printf("Id trouvé\n");
    else printf("Id non trouvé\n");
    printf("====================\n");
    pAVL s = recherche(avl,"CE100000E");
    if (s){
        printf("Id trouvé\n");
    }
    else {
        printf("Id non trouvé\n");
    }


    printf("====================\n");
    printf("Affichage après remplissage\n");
    afficherAVL(avl,NULL);
    */

    int taille_m;
    int taille_p;
    int n_max = 10;
    int n_min = 50;
    char* critere_trie = argsv[1];

    Dictionnaire* n_meilleurs = nUsinesOptimise(avl, n_max, critere_trie, 1, &taille_m); // max=1 pour top 5
    Dictionnaire* n_pire = nUsinesOptimise(avl,n_min,critere_trie,0,&taille_p);

    qsort(n_meilleurs,taille_m, sizeof(Dictionnaire),trieDict);
    qsort(n_pire,taille_p,sizeof(Dictionnaire),trieDict);

    jolieAffichage(n_meilleurs,1,taille_m,critere_trie);
    jolieAffichage(n_pire,0,taille_p,critere_trie);

    char chemin[64] = "";
    ecrireUsine(n_meilleurs,taille_m,chemin,1);
    chemin[0] = '\0';
    ecrireUsine(n_pire,taille_p,chemin,0);


    free(n_meilleurs);
    free(n_pire);
    libererAVL(avl);
    printf("Mémoire libérée\n");
    return 0;
}
