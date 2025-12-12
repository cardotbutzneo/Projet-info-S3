set title "Volume par usine"
set xlabel "Usines"
set ylabel "Volume (k.m³)"

set datafile separator ";"

set style data histogram
set style histogram rowstacked
set style fill solid 1.0 border -1
set boxwidth 0.8

set xtics rotate by -45
set key outside right top
set rmargin 12
set yrange [0:*]
set xtics nomirror
set ytics nomirror

set terminal pngcairo size 1200,600 enhanced font "Verdana,10"


# (affichage pastel empilé)
cap_col = "#DFDFFF"
capte_col = "#FFA0A0"
traite_col = "#DFFFDF"

#####################################################################
# ----------------------   GRAPH MAX   ------------------------------
#####################################################################
set output "gnuplot/graphique/volume_max_usines.png"

plot \
    "gnuplot/data/usine_max.dat" using 2:xtic(1) lc rgb cap_col title "Capacité", \
    "" using 3 lc rgb capte_col title "Volume capté", \
    "" using 4 lc rgb traite_col title "Volume traité"


#####################################################################
# ----------------------   GRAPH MIN   ------------------------------
#####################################################################
set output "gnuplot/graphique/volume_min_usines.png"
set yrange[1080:*]

plot \
    "gnuplot/data/usine_min.dat" using 2:xtic(1) lc rgb cap_col title "Capacité", \
    "" using 3 lc rgb capte_col title "Volume capté", \
    "" using 4 lc rgb traite_col title "Volume traité"  