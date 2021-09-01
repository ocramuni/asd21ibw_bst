set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set xrange [-20000:]
set key right bottom
set style fill transparent solid 0.5 noborder
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'avl_mad.pdf'
plot "output_median.txt" using 1:($4+$5):($4-$5) with filledcurve fc "turquoise" notitle, "" using 1:4 with linespoints pt 5 ps 0.1 lw 1 lc "web-blue" title "AVL Binary Tree"
