#!/bin/bash

source ./bash/cmd.sh
source ./bash/fonction.sh

#exemple de lancement ./launch.sh [arg1 : cmd] [arg2 : help]

#on vérifit les dépendances avant le lancement
verifDependance
if [ "$1" = "-r" ] || [ "$1" = "--run" ];then
    if { [ "$2" = "--force" ] || [ "$3" = "--force" ]; } && [ "$?" -eq 0 ];then
        echo "Vous compilez avec une ou plusieurs librairies manquantes (mode --force)."
        echo "Vous n'aurez donc pas accès à tout le code."
        verif_flag=1 #dépendance non installé, pas acces aux graphique
    fi
fi
if [ "$?" -eq 1 ];then
    echo "Erreur : Il manque une ou plusieurs dépendances pour compiler."
    echo "Utilisez l'option --force pour compiler malgré tout."
    exit 1
else
    verif_flag=0
fi


#éxécution du code si les conditions sont réuni

if [ "$1" = "-r" ] || [ "$1" = "--run" ]; then
    if [ "$#" -gt 1 ] && { [ "$2" != "--force" ] && [ "$3" != "--force" ]; }; then
        echo "Erreur : L'option '$1' ne doit pas être suivie d'autres arguments (sauf --force)." >&2
        echo "Utilisation correcte : ./launch.sh -r [--force] ou ./launch.sh --run [--force]" >&2
        exit 1
    else
        make
    fi

elif [ "$1" = "-c" ] || [ "$1" = "--clean" ];then
    if [ "$#" -gt 1 ];then
        echo "Erreur : l'option '$1' ne doit pas etre suivit d'autres arguments."
        echo "Utilisation correcte : ./launch.sh -c ou ./launch.sh --clean"
    else
        make clean
    fi

elif [ "$2" = "--help" ] || [ "$2" = "-h" ];then
    aide "$1"
    exit 0
elif [ "$1" = "-h" ] || [ "$1" = "--help" ];then
    if [ -z "$2" ];then
        echo "exemple d'utilisation : <./launch.sh [arg1 : cmd] [arg2 : help]>"
    fi
    if [ "$2" = "-a" ] || [ "$2" = "--all" ];then
        afficherDoc
        exit 0
    else
        echo "pour afficher toute la documentation saisissez : -h/--help -a/--all"
    fi
elif [ "$1" = "--arbo" ] && [ "$#" -eq 1 ];then
    arboraissance
    exit 0
elif [ "$1" = "histo" ] && [ $verif_flag -eq 0 ];then #non acces aux graphiques si gnuplot n'est pas installé
    creerFichierData "$2"
    if [ "$2" = "max" ];then
    #fonction
    echo "appel de la fonction pour max"
    elif [ "$2" = "src" ];then
    echo "appel de la fonction pour src"
    #fonction
    elif [ "$2" = "real" ];then
    echo "appel de la fonction pour real"
    #fonction
    fi
elif [ "$1" = "leaks" ];then
    if [ -z "$2" ];then
    echo "argument manquant pour la commande <leaks>"
    else #fonction
    echo "appel de la fonction pour leaks"
    fi
elif [ -z "$1" ];then
    echo "Erreur : le programme ne peut pas etre compiler sans option."
    echo "Ajouter -r ou --run pour compiler."
    echo "Exemple : ./launch -r [arg2] [arg3] ou ./launch --run [arg2] [arg3]"
else
    echo "Commande non trouvée"
fi
exit 0