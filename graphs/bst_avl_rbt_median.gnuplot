set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set xrange [-20000:]
set grid xtics mxtics ytics mytics
set key right bottom
set style fill transparent solid 0.5 noborder
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'bst_avl_rbt_median.pdf'
plot "output_median.txt" using 1:($4+$5):($4-$5) with filledcurve fc "turquoise" notitle, "" using 1:4 smooth mcspline lw 2 lc "web-blue" title "AVL", "" using 1:($2+$3):($2-$3) with filledcurve fc "light-red" notitle, "" using 1:2 smooth mcspline lw 2 lc "red" title "BST", "" using 1:($6+$7):($6-$7) with filledcurve fc "light-green" notitle, "" using 1:6 smooth mcspline lw 2 lc "web-green" title "RBT"
