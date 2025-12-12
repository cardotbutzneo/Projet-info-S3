set datafile separator ";"

set title "Volume par usine"
set xlabel "Usines"
set ylabel "Volume (m³)"

set style data boxes
set boxwidth 0.6
set style fill solid 0.7 border -1

set xtics rotate by -45
set key outside right top
set rmargin 12

set terminal pngcairo size 1200,600 enhanced font "Verdana,10"

set style increment userstyles
set style line 1 lc rgb "#377eb8"
set style line 2 lc rgb "#e41a1c"

if (!exists("ARG1") || strlen(ARG1) == 0) {
    ARG1 = "capacite"
}

print "Champ utilisé :", ARG1


# -------- Graphique MAX --------
set output sprintf("gnuplot/graphique/volume_max_usines_%s.png", ARG1)
plot "gnuplot/data/usine_max.dat" using 2:xtic(1) with boxes ls 1 title "Max"

# -------- Graphique MIN --------
set output sprintf("gnuplot/graphique/volume_min_usines_%s.png", ARG1)
plot "gnuplot/data/usine_min.dat" using 2:xtic(1) with boxes ls 2 title "Min"
