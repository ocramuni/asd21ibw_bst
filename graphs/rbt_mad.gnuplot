set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set xrange [-20000:]
set key right bottom
set style fill transparent solid 0.5 noborder
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'rbt_mad.pdf'
plot "output_median.txt" using 1:($6+$7):($6-$7) with filledcurve fc "light-green" notitle, "" using 1:6 with linespoints pt 5 ps 0.1 lw 1 lc "web-green" title "Red-Black Tree"
