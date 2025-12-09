# Séparateur des données
set datafile separator ";"

# Configuration du graphique
set title "Histogramme des données"
set xlabel "Valeurs"
set ylabel "Fréquence"
set boxwidth 0.8
set style fill solid 0.5 border -1

# Configuration du terminal et du fichier de sortie
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set output "gnuplot/graphique/graphique.png"

# Tracé de l'histogramme (colonne 4)
plot "gnuplot/data/usine.dat" using 4:(1) smooth frequency with boxes title "Histogramme"
