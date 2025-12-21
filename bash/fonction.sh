#!/bin/bash

# macro de couleur

ROUGE="\e[31m"
VERT="\e[32m"
JAUNE="\033[33m"
VIOLET="\e[35m"
RESET="\e[0m"

verifDependance() {
    local args=("python3")

    for cmd in "${args[@]}"; do
        if ! command -v "$cmd" &> /dev/null; then
            echo -e "${ROUGE}Erreur : La dépendance <$cmd> n'est pas installée. Veuillez l'installer et réessayer. ${RESET}"
            echo "Pour compiler sans les dépendances ajoutez '--force'."
            echo "Exemple : ./launch.sh [arg1] [arg2] --force -> compilation sans dépendances."
            echo -e "${ROUGE}Attention ! : Certaines fonctionnalités ne seront pas présentes.${RESET}"
            return 1
        fi
    done
    return 0
}

#fonction inutile mais drole
BarreDeProgression() {
    local cmp=0
    local bar=""
    if [[ -z "$1" ]];then
        local max=10 # valeur arbitraire
    else 
        local max="$1"  # Nombre total d'étapes en s
    fi
    while [ $cmp -le $max ]; do
        # Ajoute un "#" à la barre à chaque itération
        bar="${bar}#"
        # Affiche la barre sur la même ligne
        printf "\rChargement : [%s%s] %d%%" "$bar" "$(printf '%*s' $((max - cmp)) | tr ' ' '-')" $((cmp * 100 / max))
        sleep 1
        ((cmp++))
    done
    # Saut de ligne à la fin
    echo
    return 0
}

afifchageInit(){ # idem
    echo "Adding extra memory RAM for better performence"
    BarreDeProgression 15
    if [[ "$?" -eq 0 ]];then
        echo "Donne..."
        echo "1Tb memory RAM was add to your pc..."
    else
        echo "Failed of the test, you're sucks"
    fi
    echo "Downloading quantum chip for better performence"
    BarreDeProgression 5
    if [[ "$?" -eq 0 ]];then
        echo "Donne..."
    else
        echo "Quatum chips cannot be download..."
        echo "Exit..."
    fi
    echo "Working with Chatpgt..."
    BarreDeProgression 10
    if [[ "$?" -eq 0 ]];then
        echo "Donne..."
    else 
        echo "We detect a probem with Chatgpt, retry later"
    fi

}

###

erreur() { # fonction d'erreur pour le shell
    printf "%b\n" "${ROUGE}$1${RESET}" >> output/stderr
}

fuites_tri() { #vu qu'ici on a besoin de tous les tronçons liés à l'usine  on ne peut pas utiliser un filtrage classique
    if (( $# != 2)); then
    echo "Pb argument"
    echo "Exemple d'utilisation : Facility complex #RH400057F"
    echo "Usage: fuites_tri <Type ID_Usine>"
    return 1
    fi
    grep -wF "$2" ./"$1" | ./main "leaks" "$2" > output/stdout 2> output/stderr  #grep w renvoie exactement les lignes contenant cette chaîne de caractère (AKA l'ID)
    if [ "$?" -eq 1 ];then
        echo "Erreur dans le C"
    fi
    return 0

}

trie_graphique(){ # génère le graphique
    if (($# != 3));then
        echo "Erreur : manque d'argument" >> output/stderr
        return 1
    fi
    echo "Réalisation des graphiques"
    {
        grep -E "^-;[^-;]+;-;" ./"$3"
        echo "sources"
        grep -E "^-;[^;]*;[^-;]*;[^-;]*;[^;]*" ./"$3"
    } | ./main "histo" "$2" > output/stdout 2> output/stderr

    if [ "$?" -eq 1 ];then
    echo "Erreur dans le C"
    fi

    return 0
}