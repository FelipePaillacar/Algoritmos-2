# ═══════════════════════════════════════════════════════════════
# graficos.gp  —  Tarea 2 "Divide y Vencerás"
# Genera los 13 gráficos desde los CSV de experimentos.c
#
# Uso:    gnuplot graficos.gp
# Salida: plots/g1_*.png  ...  plots/g13_*.png
#
# Decisión de escala:
#   Lineal  → algoritmos del mismo orden (diferencias pequeñas)
#   Log Y   → mezcla de órdenes O(n log n) / O(n²) / O(n)
#             → diferencias de 10x-1000x que aplastan la escala lineal
# ═══════════════════════════════════════════════════════════════

set terminal pngcairo enhanced font "Arial,11" size 900,600
set datafile separator ","
set grid lc rgb "#dddddd" lt 1 lw 0.5
system("mkdir -p plots")

# ── Paleta de colores (misma del informe) ──────────────────────
PURPLE = "#7f77dd"
TEAL   = "#1d9e75"
CORAL  = "#d85a30"
BLUE   = "#378add"
PINK   = "#d4537e"
AMBER  = "#ef9f27"
GREEN  = "#639922"
GRAY   = "#888780"

set style line 1 lc rgb PURPLE lw 2 pt 7  ps 0.9   # filled circle
set style line 2 lc rgb TEAL   lw 2 pt 5  ps 0.9   # filled square
set style line 3 lc rgb CORAL  lw 2 pt 9  ps 0.9   # filled triangle
set style line 4 lc rgb BLUE   lw 2 pt 11 ps 0.9   # filled diamond
set style line 5 lc rgb PINK   lw 2 pt 13 ps 0.9   # filled pentagon
set style line 6 lc rgb AMBER  lw 2 pt 15 ps 0.9   # filled hexagon
set style line 7 lc rgb GREEN  lw 2 pt 3  ps 0.9   # asterisk
set style line 8 lc rgb GRAY   lw 2 pt 1  ps 0.9   # plus

# Macro de ayuda: filtra filas donde la columna 2 (string) == CASO
# Uso dentro de plot: using 1:(FILTRO("caso") ? $3 : 1/0)
# (1/0 = undefined → gnuplot omite el punto)


# ══════════════════════════════════════════════════════════════
# G1 — Umbral óptimo de Merge Sort optimizado
#   CSV: N, k1, k10, k30, k60
#   ESCALA LINEAL: todos son O(n log n), diferencias pequeñas y
#   visibles en escala lineal → se busca el mínimo de la curva.
# ══════════════════════════════════════════════════════════════
set output "plots/g1_merge_umbrales.png"
set title  "G1 – Impacto del umbral en Merge Sort optimizado\n(caso promedio)"
set xlabel "Tamaño de entrada (n)"
set ylabel "Tiempo promedio (s)"
set key    top left
unset logscale
set yrange [0:*]

plot "data/g1_merge_umbrales.csv" \
     using 1:2 title "k = 1"  with linespoints ls 1, \
     ""        using 1:3 title "k = 10" with linespoints ls 2, \
     ""        using 1:4 title "k = 30" with linespoints ls 3, \
     ""        using 1:5 title "k = 60" with linespoints ls 4

print "✓ G1  plots/g1_merge_umbrales.png"

# ══════════════════════════════════════════════════════════════
# G2-G4 — Merge Sort clásico vs optimizado (3 casos)
#   CSV: N, caso, clasico, optimizado
#   ESCALA LINEAL: ambos son O(n log n); la escala lineal
#   muestra la ganancia real del umbral en segundos absolutos.
# ══════════════════════════════════════════════════════════════
DATA_MERGE = "data/g2_g3_g4_merge_casos.csv"

# ── G2: mejor caso ────────────────────────────────────────────
set output "plots/g2_merge_mejor_caso.png"
set title  "G2 – Merge Sort clásico vs optimizado\n(mejor caso)"
set yrange [0:*]
unset logscale

plot DATA_MERGE \
     using 1:(stringcolumn(2) eq "mejor" ? $3 : 1/0) \
           title "Clásico"    with linespoints ls 1, \
     ""    using 1:(stringcolumn(2) eq "mejor" ? $4 : 1/0) \
           title "Optimizado" with linespoints ls 2

print "✓ G2  plots/g2_merge_mejor_caso.png"

# ── G3: peor caso ─────────────────────────────────────────────
set output "plots/g3_merge_peor_caso.png"
set title  "G3 – Merge Sort clásico vs optimizado\n(peor caso)"

plot DATA_MERGE \
     using 1:(stringcolumn(2) eq "peor" ? $3 : 1/0) \
           title "Clásico"    with linespoints ls 1, \
     ""    using 1:(stringcolumn(2) eq "peor" ? $4 : 1/0) \
           title "Optimizado" with linespoints ls 2

print "✓ G3  plots/g3_merge_peor_caso.png"

# ── G4: caso promedio ─────────────────────────────────────────
set output "plots/g4_merge_promedio.png"
set title  "G4 – Merge Sort clásico vs optimizado\n(caso promedio)"

plot DATA_MERGE \
     using 1:(stringcolumn(2) eq "promedio" ? $3 : 1/0) \
           title "Clásico"    with linespoints ls 1, \
     ""    using 1:(stringcolumn(2) eq "promedio" ? $4 : 1/0) \
           title "Optimizado" with linespoints ls 2

print "✓ G4  plots/g4_merge_promedio.png"

# ══════════════════════════════════════════════════════════════
# G5-G7 — Quick Sort: 4 variantes de pivote × 3 casos
#   CSV: N, caso, ultimo, primero, aleatorio, mediana3
#
#   G5 (mejor):   lineal  → todas las variantes dan O(n log n)
#   G6 (peor):    LOG Y   → último/primero degenera a O(n²),
#                           aleatorio/mediana3 se mantiene O(n log n)
#                           → diferencia de 100x–1000x
#   G7 (promedio): lineal → convergen a O(n log n)
# ══════════════════════════════════════════════════════════════
DATA_QUICK = "data/g5_g6_g7_quick_pivotes.csv"

# ── G5: mejor caso ────────────────────────────────────────────
set output "plots/g5_quick_mejor_caso.png"
set title  "G5 – Quick Sort: variantes de pivote\n(mejor caso)"
set ylabel "Tiempo promedio (s)"
unset logscale
set yrange [0:*]

plot DATA_QUICK \
     using 1:(stringcolumn(2) eq "mejor" ? $3 : 1/0) title "Último"    with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $4 : 1/0) title "Primero"   with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $5 : 1/0) title "Aleatorio" with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $6 : 1/0) title "Mediana-3" with linespoints ls 4

print "✓ G5  plots/g5_quick_mejor_caso.png"

# ── G6: peor caso — LOG SCALE ─────────────────────────────────
set output "plots/g6_quick_peor_caso.png"
set title  "G6 – Quick Sort: variantes de pivote\n(peor caso) — escala logarítmica"
set ylabel "Tiempo promedio (s)  [escala log]"
set logscale y
unset yrange

plot DATA_QUICK \
     using 1:(stringcolumn(2) eq "peor" ? $3 : 1/0) title "Último"    with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $4 : 1/0) title "Primero"   with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $5 : 1/0) title "Aleatorio" with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $6 : 1/0) title "Mediana-3" with linespoints ls 4

print "✓ G6  plots/g6_quick_peor_caso.png  [log Y]"

# ── G7: caso promedio ─────────────────────────────────────────
set output "plots/g7_quick_promedio.png"
set title  "G7 – Quick Sort: variantes de pivote\n(caso promedio)"
set ylabel "Tiempo promedio (s)"
unset logscale
set yrange [0:*]

plot DATA_QUICK \
     using 1:(stringcolumn(2) eq "promedio" ? $3 : 1/0) title "Último"    with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $4 : 1/0) title "Primero"   with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $5 : 1/0) title "Aleatorio" with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $6 : 1/0) title "Mediana-3" with linespoints ls 4

print "✓ G7  plots/g7_quick_promedio.png"

# ══════════════════════════════════════════════════════════════
# G8-G10 — Tarea 1 vs Tarea 2: todos los algoritmos (3 casos)
#   CSV: N, caso, bubble, insertion, selection, cocktail, merge, quick
#
#   LOG Y en los 3 casos: Bubble/Insertion/Selection/Cocktail son
#   O(n²) mientras Merge/Quick son O(n log n). Con n=5000 la
#   diferencia ya es ~10x, aplastando la escala lineal.
# ══════════════════════════════════════════════════════════════
DATA_COMP = "data/g8_g9_g10_t1_vs_t2.csv"

set logscale y
unset yrange
set ylabel "Tiempo promedio (s)  [escala log]"

# ── G8: mejor caso ────────────────────────────────────────────
set output "plots/g8_t1vst2_mejor_caso.png"
set title  "G8 – Tarea 1 vs Tarea 2: todos los algoritmos\n(mejor caso) — escala logarítmica"

plot DATA_COMP \
     using 1:(stringcolumn(2) eq "mejor" ? $3 : 1/0) title "Bubble Sort"    with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $4 : 1/0) title "Insertion Sort" with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $5 : 1/0) title "Selection Sort" with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $6 : 1/0) title "Cocktail Sort"  with linespoints ls 4, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $7 : 1/0) title "Merge Sort"     with linespoints ls 5, \
     ""   using 1:(stringcolumn(2) eq "mejor" ? $8 : 1/0) title "Quick Sort"     with linespoints ls 6

print "✓ G8  plots/g8_t1vst2_mejor_caso.png  [log Y]"

# ── G9: peor caso ─────────────────────────────────────────────
set output "plots/g9_t1vst2_peor_caso.png"
set title  "G9 – Tarea 1 vs Tarea 2: todos los algoritmos\n(peor caso) — escala logarítmica"

plot DATA_COMP \
     using 1:(stringcolumn(2) eq "peor" ? $3 : 1/0) title "Bubble Sort"    with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $4 : 1/0) title "Insertion Sort" with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $5 : 1/0) title "Selection Sort" with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $6 : 1/0) title "Cocktail Sort"  with linespoints ls 4, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $7 : 1/0) title "Merge Sort"     with linespoints ls 5, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $8 : 1/0) title "Quick Sort"     with linespoints ls 6

print "✓ G9  plots/g9_t1vst2_peor_caso.png  [log Y]"

# ── G10: caso promedio ────────────────────────────────────────
set output "plots/g10_t1vst2_promedio.png"
set title  "G10 – Tarea 1 vs Tarea 2: todos los algoritmos\n(caso promedio) — escala logarítmica"

plot DATA_COMP \
     using 1:(stringcolumn(2) eq "promedio" ? $3 : 1/0) title "Bubble Sort"    with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $4 : 1/0) title "Insertion Sort" with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $5 : 1/0) title "Selection Sort" with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $6 : 1/0) title "Cocktail Sort"  with linespoints ls 4, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $7 : 1/0) title "Merge Sort"     with linespoints ls 5, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $8 : 1/0) title "Quick Sort"     with linespoints ls 6

print "✓ G10 plots/g10_t1vst2_promedio.png  [log Y]"

# ══════════════════════════════════════════════════════════════
# G11-G12 — Algoritmos de búsqueda (peor caso y promedio)
#   CSV: N, caso, secuencial, binaria_iter, binaria_rec,
#             binaria_rango, exponencial, interpolacion
#
#   LOG Y en ambos: Secuencial es O(n), el resto O(log n).
#   Con n=50 000 la diferencia es ~16x en promedio y mucho
#   más en peor caso. La escala lineal aplana todas las
#   variantes de búsqueda binaria en cero.
# ══════════════════════════════════════════════════════════════
DATA_BUS = "data/g11_g12_busqueda.csv"

set logscale y
set ylabel "Tiempo promedio (s)  [escala log]"

# ── G11: peor caso ────────────────────────────────────────────
set output "plots/g11_busqueda_peor_caso.png"
set title  "G11 – Algoritmos de búsqueda\n(peor caso) — escala logarítmica"

plot DATA_BUS \
     using 1:(stringcolumn(2) eq "peor" ? $3 : 1/0) title "Secuencial (T1)"     with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $4 : 1/0) title "Binaria iter. (T1)" with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $5 : 1/0) title "Binaria rec."       with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $6 : 1/0) title "Binaria rangos"     with linespoints ls 4, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $7 : 1/0) title "Exponencial"        with linespoints ls 5, \
     ""   using 1:(stringcolumn(2) eq "peor" ? $8 : 1/0) title "Interpolación"      with linespoints ls 6

print "✓ G11 plots/g11_busqueda_peor_caso.png  [log Y]"

# ── G12: caso promedio ────────────────────────────────────────
set output "plots/g12_busqueda_promedio.png"
set title  "G12 – Algoritmos de búsqueda\n(caso promedio) — escala logarítmica"

plot DATA_BUS \
     using 1:(stringcolumn(2) eq "promedio" ? $3 : 1/0) title "Secuencial (T1)"     with linespoints ls 1, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $4 : 1/0) title "Binaria iter. (T1)" with linespoints ls 2, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $5 : 1/0) title "Binaria rec."       with linespoints ls 3, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $6 : 1/0) title "Binaria rangos"     with linespoints ls 4, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $7 : 1/0) title "Exponencial"        with linespoints ls 5, \
     ""   using 1:(stringcolumn(2) eq "promedio" ? $8 : 1/0) title "Interpolación"      with linespoints ls 6

print "✓ G12 plots/g12_busqueda_promedio.png  [log Y]"

# ══════════════════════════════════════════════════════════════
# G13 — Quick Select: mejor caso vs peor caso
#   CSV: N, mejor, peor
#
#   LOG Y: mejor caso O(n) vs peor caso O(n²).
#   Con n=50 000 la razón peor/mejor es ~50 000x en teoría;
#   en la práctica será 10x-100x dependiendo del input.
# ══════════════════════════════════════════════════════════════
set output "plots/g13_quickselect.png"
set title  "G13 – Quick Select: mejor caso vs peor caso\n(escala logarítmica)"
set xlabel "Tamaño de entrada (n)"
set ylabel "Tiempo promedio (s)  [escala log]"
set logscale y
set key top left

plot "data/g13_quickselect.csv" \
     using 1:2 title "Mejor caso — k=n/2, entrada aleatoria" with linespoints ls 2, \
     ""        using 1:3 title "Peor caso  — k=0,   entrada ordenada"  with linespoints ls 1

print "✓ G13 plots/g13_quickselect.png  [log Y]"

# ══════════════════════════════════════════════════════════════
print ""
print "════════════════════════════════════════════════"
print "  13 gráficos generados en  plots/"
print ""
print "  Escala lineal : G1  G2  G3  G4  G5  G7"
print "  Escala log Y  : G6  G8  G9  G10 G11 G12 G13"
print "════════════════════════════════════════════════"