#/bin/bash
wc -m alice.txt
wc -w alice.txt
grep  -io "^[А-Я][^.\n]*королева[^.\n]*[.!؟]" alice.txt 
sed -n '/ГЛАВА СЕДЬМАЯ/,/ГЛАВА ВОСЬМАЯ/p' alice.txt  |  awk '{for (i=1; i<=NF; i++) { if ($i ~ /^[А-Я]/) {print $i}}}' 
