#include "main.h"
#include "arbres.h"
#include "histo.h"
#include <string.h>
#include <time.h>
  

void printErreur(const char *msg) {
    if (!msg) return;
    time_t t = time(NULL);
    struct tm *date = localtime(&t);
    char champ_date[32];
    strftime(champ_date, sizeof(champ_date), "%Y-%m-%d %H:%M:%S", date);

    fprintf(stderr, "[%s] Erreur : %s\n", champ_date, msg);
}

// made by chatgpt (j'ai compris !)
// Fonction utilitaire pour trouver l'index de la valeur extrême dans le tableau
int indexExtreme(pUsine* tab, int n, int max, int critere) {
    int idx = 0;

    for (int i = 1; i < n; i++) {
        unsigned long va, vb;

        switch (critere) {
            case 0: va = tab[i]->capacite;    vb = tab[idx]->capacite;    break;
            case 1: va = tab[i]->v_capte;     vb = tab[idx]->v_capte;     break;
            case 2: va = tab[i]->v_traite;    vb = tab[idx]->v_traite;    break;
        }

        if ((max && va < vb) || (!max && va > vb))
            idx = i;
    }
    return idx;
}

void remplirTopN(pAVL avl, pUsine* top, int n, int *cmp, char *critere, int max) {
    if (!avl) return;

    remplirTopN(avl->fg, top, n, cmp, critere, max);

    int crit = (strcmp(critere, "max") == 0) ? 0 :
               (strcmp(critere, "src") == 0) ? 1 :
               (strcmp(critere, "real") == 0) ? 2 : -1;

    unsigned long val =
        (crit == 0) ? avl->usine->capacite :
        (crit == 1) ? avl->usine->v_capte :
                       avl->usine->v_traite;

    // Si on n’a pas encore rempli
    if (*cmp < n) {
        top[*cmp] = avl->usine;
        (*cmp)++;
    }
    else {
        int idx = indexExtreme(top, n, max, crit);

        unsigned long vref =
            (crit == 0) ? top[idx]->capacite :
            (crit == 1) ? top[idx]->v_capte :
                           top[idx]->v_traite;

        if ((max && val > vref) || (!max && val < vref)) {
            top[idx] = avl->usine;
        }
    }

    remplirTopN(avl->fd, top, n, cmp, critere, max);
}

pUsine* nUsinesOptimise(pAVL avl, int n, char *critere, int max, int *taille) {
    if (!avl || n <= 0) return NULL;

    pUsine *top = malloc(sizeof(pUsine) * n);
    int count = 0;

    remplirTopN(avl, top, n, &count, critere, max);
    *taille = count;

    return top;
}

int trieDict(const void* a, const void* b) {

    const Usine* ua = *(const Usine**)a;
    const Usine* ub = *(const Usine**)b;

    unsigned long sa = 0;
    unsigned long sb = 0;

    switch (critere_trie_global) {
        case MAX:
            sa = ua->capacite;
            sb = ub->capacite;
            break;
        case SRC:
            sa = ua->v_capte;
            sb = ub->v_capte;
            break;
        case REAL:
            sa = ua->v_traite;
            sb = ub->v_traite;
            break;
    }

    return (sa > sb) - (sa < sb);

}

void lireFichier(pAVL *avl) {

    if (!avl) {
        printErreur("Erreur : AVL NULL\n");
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), stdin)) {

        trim(buffer);  // IMPORTANT : enlever \n avant tout

        // ---- Détection du séparateur ----
        if (strcmp(buffer, "sources") == 0) {
            remplirAVL(avl);
            return;
        }

        // ---- Allocation sécurisée ----
        pUsine usine = calloc(1, sizeof(Usine));   // sécurise tous les champs
        if (!usine) {
            printErreur("Erreur : malloc Usine\n");
            return;
        }

        // ---- Parsing ----
        char *token = strtok(buffer, ";");
        int i = 0;

        while (token) {
            trim(token);

            switch (i) {
                case 1:  // ID
                    usine->id = strdup(token);
                    break;

                case 3:  // capacité
                    usine->capacite = strtoul(token, NULL, 10);
                    break;
            }

            token = strtok(NULL, ";");
            i++;
        }

        if (!usine->id) {
            printErreur("Erreur : ID invalide\n");
            free(usine);
            continue;
        }

        // ---- Initialisation des volumes ----
        usine->v_capte = 0;
        usine->v_traite = 0;

        // ---- Insertion dans l’AVL ----
        *avl = ajouterAVLUsine(*avl, usine);
    }
}



void remplirAVL(pAVL *avl) {

    if (!avl) {
        printErreur("Erreur : AVL NULL\n");
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), stdin)) {

        trim(buffer);
        if (buffer[0] == '\0') continue;  // ligne vide

        char *token = strtok(buffer, ";");
        if (!token) continue;

        // Ignorer 2e token
        token = strtok(NULL, ";");
        if (!token) continue;

        // ---- Récupérer ID-----
        token = strtok(NULL, ";");   // 3e token = ID
        if (!token) continue;
        trim(token);

        pAVL res = recherche(*avl, token);
        if (!res || !res->usine) {
            continue;  // ID introuvable → OK
        }

        // ---- Volume capté ----
        token = strtok(NULL, ";");
        if (token) {
            trim(token);
            res->usine->v_capte += strtoul(token, NULL, 10);
        }

        // ---- % de perte ----
        token = strtok(NULL, ";");
        if (token) {
            trim(token);
            float perte = atof(token);
            res->usine->v_traite = res->usine->v_capte * (1.0 - perte / 100.0);
        }
    }
}


void ecrireUsine(pUsine *dict, int taille, char destination[64], int type){ // (1=max, 0=min)
    if (!dict || taille <= 0) return;
    if (type > 1 || type < 0) return;
    // Fichier par défaut
    if (destination[0] == '\0' && type == 1) {
        strcpy(destination, "graphique/data/usine_max.dat");
    }
    else if (destination[0] == '\0' && type == 0){
        strcpy(destination, "graphique/data/usine_min.dat");
    }
    
    FILE *f = fopen(destination, "w");
    if (!f) {
        printErreur("Erreur : Impossible d'ouvrir le fichier de destination\n");
        return;
    }

    for (int i = 0; i < taille; i++) { // méthode d'écriture : id;capacite;v_capte;v_traite
        if (dict[i]) if (dict[i]->capacite > 0 && dict[i]->v_capte > 0 && dict[i]->v_traite > 0){
            fprintf(f, "%s;%.3f;%.3f;%.3f\n",
            dict[i]->id,
            (dict[i]->capacite/1000.0),
            (dict[i]->v_capte/1000.0),
            (dict[i]->v_traite/1000.0));
        }
    }
    fclose(f);
}

void trim(char* str) {
    if (!str) return;
    // supprime espaces et \n en fin
    size_t len = strlen(str);
    while(len > 0 && (str[len-1]=='\n' || str[len-1]==' ' || str[len-1]=='\r'))
        str[--len] = '\0';
}