#!/bin/bash

source bash/fonction.sh

debut=$(date +%s%N)

echo "Compilation"
bash launch.sh -r

if [ ! -f "main" ];then
    echo "Erreur : executable introuvable"
    exit 1
fi

clear

# test des histogramme
echo "----------------------"
echo "Test des histogrammes"

bash launch.sh c-wildwater_v3.dat histo max
bash launch.sh c-wildwater_v3.dat histo src
bash launch.sh c-wildwater_v3.dat histo real
bash launch.sh c-wildwater_v3.dat histo all

if [ "$?" -eq 1 ];then
    echo "Probleme dans la création de graphique"
    exit 1
fi

mkdir test/ &> /dev/null
mv graphique/graphique/* test/ &> /dev/null

echo "----------------------"
echo "Test des leaks avec 'Module #OG100951D'"


bash launch.sh c-wildwater_v3.dat leaks "Module #OG100951D"
bash launch.sh c-wildwater_v3.dat leaks "Unit #GV001308I"
bash launch.sh c-wildwater_v3.dat leaks "Module #UB100142L"
bash launch.sh c-wildwater_v3.dat leaks "Unit #NH001007A"

mv graphique/data/fuites.dat test/ &> /dev/null

if [ "$?" -eq 1 ];then
    echo "Probleme dans le calcul des fuites"
    exit 1
fi

echo "----------------------"
echo -e "${JAUNE}Fin des tests${RESET}"

#bash launch.sh -c -a

fin=$(date +%s%N)

temps=$(( (fin - debut) / 1000000 ))

echo -e "${VIOLET}Temps de fonctionnement (graphique + fuite) : ${temps} ms${RESET}"

exit 0