# Configuration du graphique
set title "Histogramme des données"
set xlabel "Valeurs"
set ylabel "Fréquence"
set boxwidth 0.8  # Largeur des barres de l'histogramme
set style fill solid  # Remplit les barres avec une couleur

# Vérification de l'existence de l'argument ARG1
if (!exists("ARG1")) {
    system("echo 'Erreur : fichier source introuvable' >> output/stderr")
    exit
}

# Construction du chemin vers le fichier de données
data_file = sprintf("gnuplot/data/%s", ARG1.".csv")
print data_file
# Vérification de l'existence du fichier avec différentes extensions
#if (!exists(data_file)) {
#    system("echo 'Erreur : fichier non trouvé' >> output/stderr")
#    exit
#}
# Détermination du fichier de sortie
if (ARG2 = "") {
    system("echo 'Warning : fichier de sortie non spécifié -- mis par défaut à gnuplot/graphique/".ARG1."' >> output/stdout")
    output_file = sprintf("gnuplot/graphique/%s.png", ARG1)
} else {
    output_file = sprintf("gnuplot/graphique/%s.png", ARG1)
}

# Configuration du terminal et du fichier de sortie
set terminal png
set output output_file

# Tracé de l'histogramme
plot data_file using 1:(1) smooth frequency with boxes title "Histogramme"
