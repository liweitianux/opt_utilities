#!/bin/sh

for i in *.tex
do
    ./latex2svg.sh $i
done

rm -f *.aux
rm -f *.sk
rm -f *.ps
rm -f *.dvi
rm -f *.log
