#!/bin/bash

echo "Filename | Size (bytes) | Lines of Code"
echo "--------------------------------------"

for file in *.c *.cpp; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        size=$(wc -c < "$file")
        lines=$(wc -l < "$file")
        echo "$filename | $size | $lines"
    fi
done
