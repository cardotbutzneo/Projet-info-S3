#include "main.h"
int main(int argc, char* argsv[])
{
    if (argc !=2) exit(0);
    printErrreur("hello");
    Token_liste* valeurs = NULL;
    valeurs = ouvrir_fichier(argsv[1]);
    Token_liste *temp = valeurs;
    while (temp){
        printf("type : %s\n",temp->token);
        temp = temp->suivant;
    }
    
    return 0;
}
