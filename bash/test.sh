#!/bin/bash

source bash/fonction.sh

echo "Compilation"
bash launch.sh -r

if [ ! -f "main" ];then
    echo "Erreur : executable introuvable"
    exit 1
fi

# test des histogramme
echo "----------------------"
echo "Test des histogrammes"

bash launch.sh c-wildwater_v3.dat histo all .p

if [ "$?" -eq 1 ];then
    echo "Probleme dans la création de graphique"
    exit 1
fi

echo "----------------------"
echo "Test des leaks avec 'Module #OG100951D'"


bash launch.sh c-wildwater_v3.dat leaks "Module #OG100951D"

if [ "$?" -eq 1 ];then
    echo "Probleme dans le calcul des fuites"
    exit 1
fi

echo "Fin des tests"
echo "----------------------"

bash launch.sh -c -a

exit 0