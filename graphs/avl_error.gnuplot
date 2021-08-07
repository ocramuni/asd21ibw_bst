set xlabel 'Numero nodi'
set ylabel 'Tempo (s)'
set key right bottom
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'avl_error.pdf'
plot "output_median.txt" using 1:4:5 with errorlines pt 5 ps 0.1 lw 1 lc "web-blue" title "AVL Binary Tree"
