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
    afficherAVL(avl,&i);
    printf("id : %s\n",avl->usine->id);
    //remplirAVL(avl);
    switch (recherche_i(avl,"CE100000E")){ // exemple de recherche de noeud
        case 1:
            printf("Id trouvé\n");
            break;
        default:
            printf("Id non trouvé\n");
            break;
    }
    if (recherche(avl,"CE100000E")){
        printf("Id trouvé\n");
    }
    else {
        printf("Id non trouvé\n");
    }
    i=1;
    afficherAVL(avl,&i);
    libererAVL(avl);
    printf("Mémoire libérée\n");
    return 0;
}
