#!/bin/bash

source ./bash/cmd.sh
source ./bash/fonction.sh

#exemple de lancement ./launch.sh [arg1 : cmd] [arg2 : help]
gnuplot test.gp
#on vérifit les dépendances avant le lancement
verifDependance

if [ "$2" = "--help" ] || [ "$2" = "-h" ];then
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
elif [ "$1" = "histo" ];then
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
elif [ "$1" = "-r" ] || [ "$1" = "--run" ] || [ -z "$1" ];then
    make
elif [ "$1" = "-c" ] || [ "$1" = "--clean" ];then
    make clean 
fi