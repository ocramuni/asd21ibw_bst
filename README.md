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
