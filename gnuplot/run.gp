set datafile separator ";"

set title "Volume par usine"
set xlabel "Usines"
set ylabel "Volume"

set style data boxes
set style fill solid 0.6 border -1
set boxwidth 0.6

set terminal pngcairo size 900,600 enhanced font "Verdana,10"
set output "gnuplot/graphique/volume_usines.png"

# Important : catégories en abscisse
set xtics rotate by -45

plot "gnuplot/data/usine_max.dat" using 2:xtic(1) title "Volume"
