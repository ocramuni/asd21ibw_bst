set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set xrange [-20000:]
set key right bottom
set style fill transparent solid 0.5 noborder
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'bst_mad.pdf'
plot "output_median.txt" using 1:($2+$3):($2-$3) with filledcurve fc "light-red" notitle, "" using 1:2 with linespoints pt 5 ps 0.1 lw 1 lc "red" title "Binary Search Tree"
