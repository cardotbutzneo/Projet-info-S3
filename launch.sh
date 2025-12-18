#!/bin/bash

source "bash/cmd.sh"
source "bash/fonction.sh"

liste_cmd=("histo" "leaks" "-r" "--run" "-c" "--clean")

if [ "$1" = "-h" ] || [ "$1" = "--help" ];then
    if [ "$2" = "-a" ] || [ "$2" = "--all" ];then
        afficherDoc
        exit 0
    fi
fi

prev=""
for token in "$@"; do
    if [ "$token" = "-h" ] || [ "$token" = "--help" ]; then
        # Affiche l'aide du dernier argument avant -h/--help
        if [ -z "$prev" ]; then
            echo "Aucune commande spécifiée pour l'aide"
            exit 1
        fi
        aide "$prev"
        exit 0
    fi
    prev="$token"
done

if [ "$1" != "-c" ] && [ "$1" != "--clean" ]; then
    verifDependance
    verif="$?"
    verif_flag=1  # Faux par défaut
    if [ "$verif" -eq 0 ]; then
        verif_flag=0  # Vrai si toutes dépendances présentes
    fi
fi

if [ "$1" = "-r" ] || [ "$1" = "--run" ]; then
    if [ -n "$2" ] && [ "$2" != "--force" ];then
        echo -e "${JAUNE}Argument invalide apres -r${RESET}"
        echo "-r/--run ne prend pas d'autre argument que [--force]"
        exit 1
    fi
    if [ "$verif" -eq 1 ] && [ "$2" != "--force" ]; then
        echo "Une ou plusieurs dépendances sont manquantes."
        echo "Veuillez les installer ou utiliser --force pour compiler sans."
        exit 1
    elif [ "$verif" -eq 1 ] && [ "$2" = "--force" ]; then
        echo -e "${ROUGE}Compilation forcée malgré les dépendances manquantes${RESET}"
    fi
    make
    exit 0
fi



if [ "$1" = "-c" ] || [ "$1" = "--clean" ]; then
    make clean
    if [ "$2" = "-a" ] || [ "$2" = "--all" ]; then
        if [ -n "$3" ]; then
            echo "L'argument -c ne peut prendre que [-a/--all] en paramètre"
            aide "$1"
            exit 1
        fi
        echo -e "${ROUGE}Attention : vous supprimez les graphiques et fichiers temporaires${RESET}"
        read -p "Confirmer ce choix [y/n]: " confirm
        if [ "$confirm" = "y" ]; then
            rm -rf gnuplot/graphique/* gnuplot/data/*
            echo "Suppression terminée"
        else
            echo "Opération annulée"
        fi
    fi
    exit 0
fi


if [ "$1" = "histo" ];then
    echo -e "${ROUGE}Erreur : vous devez préciser le chemin du fichier .dat en premier paramètre${RESET}"
    exit 1
fi

if [ "$2" = "histo" ]; then
    if [ ! -f "$1" ]; then
        echo -e "${ROUGE}Erreur : le fichier '$1' est introuvable${RESET}"
        exit 1
    fi
    if [ ! -f "main" ] && [ ! -f "main.exe" ]; then
        echo "Erreur : l'exécutable est introuvable. Compiler avant d'exécuter."
        exit 1
    fi
    arg="$3"
    if [ -z "$arg" ]; then
        echo "Erreur : manque d'argument pour histo (max/src/real/all)"
        aide "histo"
        exit 1
    fi
    if [[ "$arg" != "max" && "$arg" != "src" && "$arg" != "real" && "$arg" != "all" ]]; then
        echo "Argument '$arg' invalide pour histo (max/src/real/all)"
        aide "histo"
        exit 1
    fi
    time trie_graphique "$2" "$arg" "$1"
    if [ "$4" = ".p" ]; then
        python3 gnuplot/run.py "$arg"
    elif [ "$4" = ".g" ]; then
        gnuplot gnuplot/run.gp
    fi
    exit 0
fi

if [ "$2" = "leaks" ]; then
    if [ -z "$1" ];then
        echo "Erreur : chemin du fichier attendu"
        exit 1
    fi
    if [ ! -f "$1" ]; then
        echo -e "${ROUGE}Erreur : le fichier '$1' est introuvable${RESET}"
        exit 1
    fi
    if [ -z "$3" ]; then
        echo "Erreur : Identifiant de l'usine attendu pour les leaks"
        exit 1
    fi
    echo "$3"
    time fuites_tri "$1" "$3"
    exit 0
fi

echo "Commande non trouvée"
exit 1
