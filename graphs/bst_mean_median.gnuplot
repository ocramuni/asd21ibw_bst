set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set xrange [-20000:]
set key right bottom
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'bst_mean_median.pdf'
plot "output_mean.txt" using 1:2 with linespoints pt 5 ps 0.1 lw 1 lc "magenta" title "Binary Search Tree (mean)", "output_median.txt" using 1:2 with linespoints pt 5 ps 0.1 lw 1 lc "red" title "Binary Search Tree (median)"

