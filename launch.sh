#!/bin/bash

source ./bash/cmd.sh
source ./bash/fonction.sh

#exemple de lancement ./launch.sh [arg1 : cmd] [arg2 : help]

#on vérifit les dépendances avant le lancement
#verifDependance
if [ "$1" = "-r" ] || [ "$1" = "--run" ];then
    if { [ "$2" = "--force" ] || [ "$3" = "--force" ]; } && [ "$?" -eq 1 ];then
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

if [ "$2" = "--help" ] || [ "$2" = "-h" ];then
    aide "$1"
    exit 0
fi

if [ "$1" = "-r" ] || [ "$1" = "--run" ]; then
    if [ "$#" -gt 1 ] && { [ "$2" != "--force" ] && [ "$3" != "--force" ]; }; then
        echo "Erreur : L'option '$1' ne doit pas être suivie d'autres arguments (sauf --force)." >&2
        echo "Utilisation correcte : ./launch.sh -r [--force] ou ./launch.sh --run [--force]" >&2
        exit 1
    else
        make
    fi
    exit 0

elif [ "$1" = "-c" ] || [ "$1" = "--clean" ]; then
    if [ "$2" != "-a" ] && [ "$2" != "--all" ] && [ -n "$2" ]; then
        echo "Erreur : l'option '$1' ne doit être suivie que par -a/--all ou aucun argument."
        echo "Utilisation correcte : ./launch.sh -c ou ./launch.sh --clean [-a|--all]"
        exit 1
    fi

    make clean

    # Si -a ou --all est passé, supprime les graphiques sans demander
    if [ "$2" = "-a" ] || [ "$2" = "--all" ]; then
        echo "Suppression des graphiques et des données..."
        rm -rf gnuplot/graphique/* 2>/dev/null
        if [ $? -eq 0 ]; then
            echo "Suppression des graphiques réussie" >> output/stdout
        else
            echo "Aucun dossier gnuplot/graphique à supprimer" >> output/stdout
        fi
    fi

elif [ "$1" = "-h" ] || [ "$1" = "--help" ];then
    if [ -z "$2" ];then
        echo "exemple d'utilisation : <./launch.sh [arg1 : cmd] [arg2 : help]>"
        exit 1
    fi
    if [ "$2" = "-a" ] || [ "$2" = "--all" ];then
        afficherDoc
        exit 0
    else
        echo "pour afficher toute la documentation saisissez : -h/--help -a/--all"
        exit 0
    fi
elif [ "$1" = "--arbo" ] && [ "$#" -eq 1 ];then
    arboraissance
    exit 0
elif [ "$1" = "histo" ] && [ $verif_flag -eq 0 ];then #non acces aux graphiques si gnuplot n'est pas installé
    if [ "$?" -ne 0 ];then
        exit 1
    fi
    if [ "$2" = "max" ] || [ "$2" = "src" ] || [ "$2" = "real" ] || [ "$2" = "all" ];then
        echo "appel de la fonction"
        trie "$1" "$2"
        python3 gnuplot/run.py
        exit 0
    else
        echo "Commande non reconnu"
    fi
elif [ "$1" = "leaks" ];then
    if [ -z "$2" ];then
        echo "argument manquant pour la commande <leaks>"
        exit 1
    else #fonction
        echo "appel de la fonction pour leaks"
        exit 0
    fi
elif [ -z "$1" ];then
    echo "Erreur : le programme ne peut pas etre compiler sans option." >> output/stderr
    echo "Ajouter -r ou --run pour compiler."
    echo "Exemple : ./launch -r [arg2] [arg3] ou ./launch --run [arg2] [arg3]"
    exit 1
else
    echo "Commande non trouvée"
    exit 1
fi
exit 0