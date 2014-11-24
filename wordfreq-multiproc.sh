#!/bin/bash

# wordfreq-multiproc.sh
# Anton Paar Shapetec homeassignment
# Erwin Nindl, 01.07.2014
# Email: <erwin@nindl.eu>

set -e  # halt if single command returns error
set -u  # check if variables are set

for file in "$@"
do
  (
    sed 's/\s/\n/g' "$file" | grep -v '^\s*$' | sort | uniq -c
  )&
done | awk '{
   freq[ $2 ] += $1;
} END {
   for (word in freq)
      printf "%-23s%s\n", word, freq[word];
}' | sort 

#eof
