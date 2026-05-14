set terminal pngcairo size 800,600
set output './plots/plot_f1_a_f5.png'
set title 'Comparacion de f1 a f5'
set xlabel 'n'
set ylabel 'Tiempo (s) (Escala logaritmica)'
set grid
set key left top
set datafile separator ','
set logscale y

plot 'data/comparar_Ns.csv' using 1:2 with lines title 'f1', \
     'data/comparar_Ns.csv' using 1:3 with lines title 'f2', \
     'data/comparar_Ns.csv' using 1:4 with lines title 'f3', \
     'data/comparar_Ns.csv' using 1:5 with lines title 'f4', \
     'data/comparar_Ns.csv' using 1:6 with lines title 'f5'