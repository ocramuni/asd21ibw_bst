set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set key right bottom
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'rbt_mean.pdf'
plot "output_mean.txt" using 1:6 with linespoints pt 5 ps 0.1 lw 1 lc "web-green" title "Red-Black Tree"

