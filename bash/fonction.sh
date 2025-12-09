#!/bin/bash

verifDependance() {
    local args=("gnuplot")

    for cmd in "${args[@]}"; do
        if ! command -v "$cmd" &> /dev/null; then
            printf "Erreur : La dépendance <$cmd> n'est pas installée. Veuillez l'installer et réessayer." >&2
            printf "Pour compilez sans les dépendances ajoutez '--force'."
            printf "Exemple : ./launch.sh [arg1] [arg2] --force -> compilation sans dépendance."
            printf "Attention ! : Certaine fonctionalité ne seront pas présentes."
            return 1
        fi
    done
    return 0
}

creerFichierData() {
    local args=("max" "src" "real")
    local fichier

    # Vérifier si un argument est fourni
    if [ -z "$1" ]; then
        echo "Erreur : Aucun argument fourni. Utilisation : creerFichierData [max|src|real]" >> output/stderr
        return 1
    fi
    if [ ! -d "gnuplot/data" ];then
        mkdir gnuplot/data
    fi
    # Vérifier si l'argument est valide
    local arg_valide=false
    for arg in "${args[@]}"; do
        if [ "$1" = "$arg" ]; then
            arg_valide=true
            break
        fi
    done

    if [ "$arg_valide" = false ]; then
        echo "Erreur : Argument '$1' non valide. Utilisez max, src ou real." >> output/stderr
        return 1
    fi

    # Créer le fichier
    fichier="gnuplot/data/$1.csv"
    touch "$fichier"

    # Vérifier si le fichier a été créé
    if [ ! -e "$fichier" ]; then
        echo "Erreur : Impossible de créer le fichier $fichier" >> output/stderr
        return 1
    else
        echo "Fichier $fichier créé avec succès" >> output/stdout
        return 0
    fi
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

#  OUTPUT = "output"
# ERRF= "$OUTPUT/stderr.txt"
#erreur(){
#    echo "[ERREUR] : $message" >> "$ERRF"
#}

filtrage() {
    if (( $# != 1 )); then
        echo "Erreur : manque d'argument" 
        echo "Exemple d'utilisation : "
        echo "Usage: filtrage <type>"
        echo "Types : usine jonction stockage raccordement source"
        return 1
    fi
    case "$1" in
        usine)
            grep -E "^-;[^-;]+;-;[^;]*;[^;]*" ./c-wildwater_v0.dat > gnuplot/data/usine.dat
            #./main usine
            ;;
        jonction)
            grep -E "^[^;]*;Junction #[A-Z0-9]+;Service #[A-Z0-9]+;-;" ./c-wildwater_v0.dat > gnuplot/data/jonction.dat
            #./main jonction
            ;;
        stockage)
            grep -E "^-;[^-;]*;[^-;]*;-;[^-;]*" ./c-wildwater_v0.dat > gnuplot/data/stockage.dat
            #./main stockage
            ;;
        raccordement)
            grep -E "^[^;]*;Service #[A-Z0-9]+;Cust #[A-Z0-9]+;-;[^;]*" ./c-wildwater_v0.dat > gnuplot/data/raccordement.dat
            #./main raccordement
            ;;
        source)
            grep -E "^-;[^;]*;[^-;]*;[^-;]*;[^;]*" ./c-wildwater_v0.dat > gnuplot/data/source.dat
            #./main source
            ;;
        *)
            echo "Erreur : type inconnu « $1 »"
            return 1
            ;;
    esac
}
#grep ";Storage #" ./c-wildwater_v0.dat > gnuplot/data/stockage.dat
trie(){
    liste_trie=("usine" "jonction" "stockage" "raccordement" "source")
    for trie in "${liste_trie[@]}";do
        fichier="gnuplot/data/{$trie}.dat"
        if [ ! -f "$fichier" ];then
            filtrage "$trie"
        fi
    done
}

trie "$1"