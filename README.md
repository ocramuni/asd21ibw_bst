# Code
## To configure:
```bash
cmake -S . -B cmake-build-debug
```

## To build:
```bash
cmake --build cmake-build-debug
```

## To run:
```bash
./cmake-build-debug/apps/binaryTreeTime

```


# Graphs
## To generate graphs:
Run `binaryTreeTime` with `USE_MEDIAN` option set to `0` and copy output to _output_mean.txt_ file in `./graphs`.

Run `binaryTreeTime` with `USE_MEDIAN` option set to `1` and copy output to _output_median.txt_ file in `./graphs`.

To generate graphs to compare execution time, run:

- `gnuplot -p bst_avl_rbt_mean.gnuplot` : graph in linear scale to compare all binary trees using mean execution time
- `gnuplot -p bst_avl_rbt_median.gnuplot` : graph in linear scale to compare all binary trees using median execution time and MAD

To generate graphs of Binary Search Tree, run:

- `gnuplot -p bst_mean.gnuplot` : graph in linear scale using mean execution time
- `gnuplot -p bst_median.gnuplot` : graph in linear scale using median execution time
- `gnuplot -p bst_mad.gnuplot` : graph in linear scale using median execution time and MAD
- `gnuplot -p bst_error.gnuplot` : graph in linear scale using median execution time and MAD as error bars
- `gnuplot -p bst_mean_median.gnuplot` : graph in linear scale using median and mean execution time

To generate graphs of AVL Binary Tree, run:

- `gnuplot -p avl_mean.gnuplot` : graph in linear scale using mean execution time
- `gnuplot -p avl_median.gnuplot` : graph in linear scale using median execution time
- `gnuplot -p avl_mad.gnuplot` : graph in linear scale using median execution time and MAD
- `gnuplot -p avl_error.gnuplot` : graph in linear scale using median execution time and MAD as error bars
- `gnuplot -p avl_mean_median.gnuplot` : graph in linear scale using median and mean execution time

To generate graphs of Red-Black Tree, run:

- `gnuplot -p rbt_mean.gnuplot` : graph in linear scale using mean execution time
- `gnuplot -p rbt_median.gnuplot` : graph in linear scale using median execution time
- `gnuplot -p rbt_mad.gnuplot` : graph in linear scale using median execution time and MAD
- `gnuplot -p rbt_error.gnuplot` : graph in linear scale using median execution time and MAD as error bars
- `gnuplot -p rbt_mean_median.gnuplot` : graph in linear scale using median and mean execution time


## To generate report images
To generate all pdf files needed to compile report, move to `./graphs` and run:

```bash
./generate_figures.sh
```

then copy all pdf files to `./report/images`.


# Report
## Compile report:

Generate graphs and copy them to `./report/images`. To compile report, move to `./report` and run:

```bash
pdflatex report.tex
```

# Appunti

per calcolare la mediana, serve ordinare l'array:

Why Quick Sort is preferred over MergeSort for sorting Arrays 
Quick Sort in its general form is an in-place sort (i.e. it doesn’t require any extra storage) whereas merge sort requires O(N) extra storage, N denoting the array size which may be quite expensive. Allocating and de-allocating the extra space used for merge sort increases the running time of the algorithm. Comparing average complexity we find that both type of sorts have O(NlogN) average complexity but the constants differ. For arrays, merge sort loses due to the use of extra O(N) storage space.
Most practical implementations of Quick Sort use randomized version. The randomized version has expected time complexity of O(nLogn). The worst case is possible in randomized version also, but worst case doesn’t occur for a particular pattern (like sorted array) and randomized Quick Sort works well in practice.
Quick Sort is also a cache friendly sorting algorithm as it has good locality of reference when used for arrays.
Quick Sort is also tail recursive, therefore tail call optimizations is done.

Problematiche riscontrate Durante le prime misurazioni, si era notata una
deviazione standard piuttosto elevata, indice di una grande variabilit`a nelle mi-
surazioni ottenute. Al fine di ottenere delle misurazioni migliori, cio`e meno
sensibili ad outliers e rumore, si `e scelto di utilizzare, al posto della media, la
mediana dei tempi di esecuzione e, al posto della deviazione standard, la de-
viazione mediana assoluta, definita come MAD = median (|Xi −median (X)|).
Questi indici, in quanto indici di posizione, sono pi`u robusti della media e della
deviazione standard e hanno permesso di ottenere dei tempi sperimentali pi`u
accurati e minormente affetti da errori casuali.
