#!/bin/bash

arboraissance(){
    echo "Arboraissance : "
    echo "projet"
    echo "|-/bash"
    echo "    |-main.sh"
    echo "|-/include"
    echo "    |-main.h"
    echo "|-/src"
    echo "    |-fonction.c"
    echo "    |-main.c"
    echo "|-launch.sh"
    echo "|-makefile"
    echo "|-README"
}

aide(){ # arg1 : nom de la commande
    if [ $# -eq 0 ];then #aucun argument
        echo "argument manquant pour la fonction <help> : utilisez --max, --src, --real, --leaks, -r, -c, --clean, -a, --all"
        exit 1
    fi
    if [ "$1" = "--arbo" ];then 
        if [ -f "doc/arboraissance" ];then
            cat "doc/arboraissance"
            exit 0
        fi
    fi
    if [ "$1" = "--max" ];then 
        if [ -f "doc/max" ];then
            cat "doc/max"
            exit 0
        fi
    fi 
    echo "aucune documentation trouvé pour <"$1">, utilisez -a/--all pour tout afficher." >&2
    exit 1
}

afficherDoc(){
    echo "Affichage de toute la documentation"
    echo ""
    for file in doc/*;do
        if [ -f "$file" ]; then
                cat "$file"
        fi
        echo ""
    done
}