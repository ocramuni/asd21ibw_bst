set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set key right bottom
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'rbt_error.pdf'
plot "output_median.txt" using 1:6:7 with errorlines pt 5 ps 0.1 lw 1 lc "web-green" title "Red-Black Tree"
