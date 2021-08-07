set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set key right bottom
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'bst_error.pdf'
plot "output_median.txt" using 1:2:3 with errorlines pt 5 ps 0.1 lw 1 lc "red" title "Binary Search Tree"
