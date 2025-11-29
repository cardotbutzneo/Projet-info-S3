set title "Exemple de Graphique"
set xlabel "Valeurs de X"
set ylabel "Valeurs de Y"
set terminal png
set output "graphique.png"
plot sin(x)+cos(x)
