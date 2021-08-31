set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set grid xtics mxtics ytics mytics
set key right bottom
set style fill transparent solid 0.5 noborder
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'bst_avl_rbt_mean.pdf'
plot "output_mean.txt" using 1:4 smooth mcspline lw 2 lc "web-blue" title "AVL", "" using 1:2 smooth mcspline lw 2 lc "red" title "BST", "" using 1:6 smooth mcspline lw 2 lc "web-green" title "RBT"
