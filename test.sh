#!/bin/bash

# test.sh
# Programmierbeispiel C++
# Erwin Nindl, 01.07.2014
# Email: <erwin@nindl.eu>


files="$@"
res1=`./wordfreq.sh $files|tail -n +2|sort -n`
res3=`./wordfreq --files $files|tail -n +2|sort -n`

diff -Z <(echo $res1) <(echo $res3) || exit 1

# if diffs passed, all OK
echo "Test passed"

#eof
