#!/bin/bash

# macro de couleur

ROUGE="\e[31m"
VERT="\e[32m"
JAUNE="\033[33m"
RESET="\e[0m"

verifDependance() {
    local args=("gnuplot" "python3")

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

afifchageInit(){
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
    echo
    echo
    echo "Go outside touching grass, lol player 🐒 🐒"
}

erreur() {
    printf "%b\n" "${ROUGE}$1${RESET}" >> output/stderr
}

fuites_tri() { #vu qu'ici on a besoin de tous les tronçons liés à l'usine  on ne peut pas utiliser un filtrage classique
    if (( $# != 1)); then
    echo "Pb argument"
    echo "Exemple d'utilisation : Facility complex #RH400057F"
    echo "Usage: fuites_tri <Type ID_Usine>"
    return 1
    fi
    type=$(echo "$1" | awk '{print $1}') #awk sert à séparer des chaînes de caractères avec leurs espaces afin de pouvoir créer des id 
    id=$(echo "$1" | awk '{print $2}')
    if ! grep -qwF "$id" ./c-wildwater_v3.dat; then #grep q renvoie 0 en cas de réussite ou 1 si le mot n'est pas dans la liste
        echo "Usine non existante"
        return 1
    fi
    echo "$1"
    grep -wF "$id" ./c-wildwater_v3.dat | ./main "leaks" "$1" 2>> output/stderr  #grep w renvoie exactement les lignes contenant cette chaîne de caractère (AKA l'ID)
    return 0

}

trie(){
    if (($# != 3));then
        echo "Erreur : manque d'argument" >> output/stderr
        return 1
    fi
    case "$1" in
        histo)
            {
                grep -E "^-;[^-;]+;-;" ./"$3"
                echo "sources"
                grep -E "^-;[^;]*;[^-;]*;[^-;]*;[^;]*" ./"$3"
            } | ./main "histo" "$2" 2>> output/stderr

            return 0
            ;;
        leak)        
            liste_trie=("usine" "source" "stokage" "raccordement" "jonction")
            for trie in "${liste_trie[@]}";do
                time {
                    {
                        grep -E \
                        -e "^-;[^-;]+;-;" \
                        -e "^-;[^;]*;[^-;]*;[^-;]*;[^;]*" \
                        -e "^-;[^-;]*;[^-;]*;-;[^-;]*" \
                        -e "^[^;]*;Junction #[A-Z0-9]+;Service #[A-Z0-9]+;-;" \
                        -e "^[^;]*;Service #[A-Z0-9]+;Cust #[A-Z0-9]+;-;[^;]*" \
                        "$3" \
                        
                    }
                }
            done
    esac
}

