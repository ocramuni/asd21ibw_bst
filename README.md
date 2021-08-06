# Code

TODO

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
