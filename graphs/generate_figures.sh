#!/usr/bin/env bash

for g in $(ls -1 *.gnuplot)
do
	gnuplot -p $g
done
