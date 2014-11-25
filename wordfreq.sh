#!/bin/bash

# wordfreq.sh
# Programmierbeispiel C++ 
# Erwin Nindl, 01.07.2014
# Email: <erwin@nindl.eu>

set -e  # halt if single command returns error
set -u  # check if variables are set

printf "%-23s%s\n" "Wort" "Anzahl"
cat "$@" | tr -s '[[:space:]]' '\n'|tr -d ' ' | sort | uniq -c |awk '{printf "%-23s%s\n", $2, $1 }'

#eof
