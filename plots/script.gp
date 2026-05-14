set datafile separator ","
set terminal png size 800,600
set grid

set xlabel "Tamaño de entrada (N)"
set ylabel "Tiempo de ejecución (milisegundos)"

# Gráfico 1: Algoritmos de Ordenamiento O(n log n)
set output "plots/plot_n_log_n.png"
set title "Comparación de Algoritmos Rápidos O(n log n)"
plot "data/resultados.csv" using 1:2 with lines linewidth 2 title "MergeSort", \
     "data/resultados.csv" using 1:3 with lines linewidth 2 title "QuickSort"

# Gráfico 2: Todos los algoritmos con Escala Logarítmica
set output "plots/plot_todos_log.png"
set title "Comparación General (Escala Logarítmica en Y)"
set logscale y
plot "data/resultados.csv" using 1:2 with lines linewidth 2 title "MergeSort", \
     "data/resultados.csv" using 1:3 with lines linewidth 2 title "QuickSort", \
     "data/resultados.csv" using 1:4 with lines linewidth 2 title "BubbleSort", \
     "data/resultados.csv" using 1:5 with lines linewidth 2 title "SelectionSort", \
     "data/resultados.csv" using 1:6 with lines linewidth 2 title "InsertionSort"
unset logscale y

# Gráfico 3: Comparación de algoritmos O(n^2)
set output "plots/plot_cuadraticos.png"
set title "Comparación de Algoritmos Lentos O(n^2)"
plot "data/resultados.csv" using 1:4 with lines linewidth 2 title "BubbleSort", \
     "data/resultados.csv" using 1:5 with lines linewidth 2 title "SelectionSort"