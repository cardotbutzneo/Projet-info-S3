#!/bin/bash

arboraissance(){
    echo "Arboraissance : "
    echo "projet"
    echo "|-/bash"
    echo "    |-cmd.sh"
    echo "    |-fonction.sh"
    echo "|-/doc"
    echo "    |-arbo"
    echo "    |-histo"
    echo "|-gnuplot/"
    echo "    |-/data"
    echo "        |-"
    echo "    |-graphique"
    echo "        |-"
    echo "    |-graphique.gp"
    echo "|-/include"
    echo "    |-main.h"
    echo "|-/output"
    echo "    |-stdout"
    echo "    |-stderr"
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
    if [ -f "doc/"$1"" ];then
        cat doc/"$1"
        echo
        exit 0
    fi
    echo "aucune documentation trouvé pour <'"$1"'>, utilisez -a/--all pour tout afficher." >&2
    echo "La documentation n'est diponible que pour les raccoursis de commande de compilation."
    echo "Exemple : -r -h : disponible / --run -h : indisponible"
    exit 1
}

afficherDoc(){
    echo "Affichage de toute la documentation"
    echo "------------------------------------------------"
    for file in doc/*;do
        if [ -f "$file" ]; then
                cat "$file"
        fi
        echo ""
        echo "------------------------------------------------"
    done
}

