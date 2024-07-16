#/bin/bash
FILE="/home/bruh/projects/tasks/module1/out.txt"
COUNTER="/home/bruh/projects/tasks/module1/counter.txt"
read -r C < "$COUNTER"
NEW_COUNTER=$((C+1))
echo "$NEW_COUNTER" > "$COUNTER"
echo "I run $C time" >> "$FILE"