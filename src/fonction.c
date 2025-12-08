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

void récupérer_max(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_max) { // récupère le max dans l'ABR par un parcourt infix inverse
    if (!avl || !dict || !cmp_max || *cmp_max >= MAX_CMP) {
        return; 
    }

    récupérer_max(avl->fd, dict, cmp_max);

    if (*cmp_max < MAX_CMP) {
        dict[*cmp_max].cle = avl->usine->id;
        dict[*cmp_max].valeur = avl->usine->v_traite;
        (*cmp_max)++;
    }
    récupérer_max(avl->fg, dict, cmp_max);
}

void récupérer_min(pAVL avl, Dictionnaire dict[MAX_CMP], int* cmp_min) { // récupère le min dans l'ABR par un parcourt infix 
    if (!avl || !dict || !cmp_min || *cmp_min >= MAX_CMP) {
        return; 
    }
    récupérer_min(avl->fg,dict,cmp_min);

    if (*cmp_min < MAX_CMP) {
        dict[*cmp_min].cle = avl->usine->id;
        dict[*cmp_min].valeur = avl->usine->v_traite;
        (*cmp_min)++;
    }
    récupérer_min(avl->fd, dict, cmp_min);
}

Token_liste* creerToken(const char* valeur){
    if (!valeur) return NULL;

    Token_liste* nouveau = malloc(sizeof(Token_liste));
    if (!nouveau) return NULL;
    nouveau->suivant = NULL;
    strncpy(nouveau->token, valeur, sizeof(nouveau->token));
    nouveau->token[sizeof(nouveau->token)-1] = '\0';
    return nouveau;
}

/*
Token_liste* ouvrir_fichier(const char* nom_fichier){
    char chemin[256];
    snprintf(chemin, sizeof(chemin), "gnuplot/data/%s.dat", nom_fichier);

    FILE *f = fopen(chemin, "r");
    if (!f) {
        printErreur("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }

    char buffer[256];
    Token_liste* liste = NULL;
    Token_liste* courant = NULL;

    while (fgets(buffer, sizeof(buffer), f)) {

        // enlever le \n
        buffer[strcspn(buffer, "\n")] = '\0';

        Token_liste* nouveau = creerToken(buffer);

        if (!liste) {
            liste = nouveau;
            courant = liste;
        } else {
            courant->suivant = nouveau;
            courant = nouveau;
        }
    }

    fclose(f);
    return liste;
}
*/

void lireFichier(const char* chemin_fichier, pAVL *avl) {
    if (!chemin_fichier) {
        printErreur("Impossible de connaitre l'emplacement du fichier\n");
        return;
    }

    char chemin[256];
    snprintf(chemin, sizeof(chemin), "gnuplot/data/%s.dat", chemin_fichier);
    FILE *f = fopen(chemin, "r");
    if (!f) {
        printErreur("Erreur : Impossible de lire le fichier .dat\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {

        trim(buffer); // enlever espaces et \n de la ligne entière

        pUsine usine = malloc(sizeof(Usine));
        if (!usine) { fclose(f); return; }

        char* token = strtok(buffer, ";");
        int i = 0;

        while (token) {
            trim(token); // sécuriser chaque token
            switch (i) {
                case 1: {
                    char* tmp = extraireID(token);
                    if (!tmp) break;
                    trim(tmp);
                    usine->id = strdup(tmp);
                    free(tmp);
                    break;
                }
                case 3:
                    usine->v_traite = atoi(token);
                    break;
            }
            token = strtok(NULL, ";");
            i++;
        }

        *avl = ajouterAVLUsine(*avl, usine);
    }

    fclose(f);
}

void remplirAVL(pAVL avl) {
    if (!avl) {
        printErreur("Erreur : AVL non initialisé\n");
        return;
    }

    FILE *f = fopen("gnuplot/data/source.dat", "r");
    if (!f) {
        printErreur("Erreur : impossible d'ouvrir le fichier .dat\n");
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), f)) {
        trim(buffer); // enlever espaces et \n de la ligne entière

        // Tokens
        char* token = strtok(buffer, ";");
        if (!token) continue; // ignorer ligne vide

        token = strtok(NULL, ";"); // 2e token à ignorer
        if (!token) continue;
        trim(token);

        token = strtok(NULL, ";"); // 3e token : ID de l'usine
        if (!token) continue;
        trim(token);

        char* id_token = extraireID(token);
        if (!id_token) continue;
        trim(id_token);

        pAVL usineptr = recherche(avl, id_token);
        printf("ID de l'usine lu : %s\n",id_token);
        if (!usineptr) {
            printf("Erreur de mémoire sur %s\n",id_token);
            free(id_token);
            continue; // passer à la ligne suivante
        }

        token = strtok(NULL, ";"); // volume capté
        if (token) {
            trim(token);
            usineptr->usine->v_capte += atoi(token);
        }

        float v_capte = usineptr->usine->v_capte;
        printf("v : %f\n",v_capte);
        token = strtok(NULL, ";"); // % perte
        if (token) {
            trim(token);
            usineptr->usine->v_traite = v_capte * (1.0 - atof(token));
        }

        free(id_token);
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



/*
void libérer_token(Token_liste* liste){
    while (liste){
        Token_liste* f = liste;
        liste = liste->suivant;
        free(f);
    }
}
*/