#include "main.h"
int main(int argc, char* argsv[])
{
    if (argc !=2) exit(0);
    if (!argsv) return 1;
    pAVL avl = NULL;
    int i=1;
    printf("Lecture en cours...\n");
    lireFichier("usine",&avl); // lit tout le fichier des sources et l'ajoute à l'avl
    printf("lecture réussie\n");
    printf("Affichage avant remplissage\n");
    afficherAVL(avl,&i);
    //printf("lecture ptr avl : '%s' \n",avl->usine->id);
    //printf("id : %s\n",avl->usine->id);
    remplirAVL(avl);
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
    i=1;
    printf("Affichage après remplissage\n");
    afficherAVL(avl,&i);
    libererAVL(avl);
    printf("Mémoire libérée\n");
    return 0;
}
