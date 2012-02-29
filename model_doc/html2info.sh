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
export BASENAME="`basename $1 .html`";
echo $BASENAME
#echo "" >>${BASENAME}.
echo "std::string result;">${BASENAME}.info

cat ${BASENAME}.html|while read -r line
do
line=$(echo -E "$line"|sed -e 's/\\/\\\\/g'|sed -e 's/\"/\\\"/g')
echo "result+=\"$line\";">>${BASENAME}.info
echo "result+=\"\\n\";">>${BASENAME}.info
done

echo "return result;" >>${BASENAME}.info


