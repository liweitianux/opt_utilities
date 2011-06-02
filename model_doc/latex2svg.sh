#!/bin/bash

if [ $# -eq 1 ]
then
    :
else
    echo $#
    echo "Usage $0 <base name>"
    exit
fi


# you need gs-common, pstoedit and skencil to
# get this script working
export BASENAME="`basename $1 .tex`";
echo $BASENAME

latex ${BASENAME}.tex

dvips ${BASENAME}.dvi
# Outline fonts
eps2eps -dNOCACHE ${BASENAME}.ps ${BASENAME}2.ps

# Fix bounding box
ps2epsi  ${BASENAME}2.ps  ${BASENAME}.ps
rm ${BASENAME}2.ps

# Convert to Sketch
pstoedit -f sk  ${BASENAME}.ps  ${BASENAME}.sk

# Convert to SVG
skconvert  ${BASENAME}.sk  ${BASENAME}.svg

echo -e return "\"\c" >${BASENAME}.info

cat ${BASENAME}.svg | sed -e ':a;N;$!ba;s/\n//g' -e 's/\"/\\\"/g' >>${BASENAME}.info

echo \"\; >>${BASENAME}.info

