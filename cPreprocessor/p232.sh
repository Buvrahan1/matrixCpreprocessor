#!/bin/bash

# Doğru sayıda argümanın sağlandığını kontrol eder
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_file.c>"
    exit 1
fi

# C kodunu derle ve çalıştır
gcc -o expanded.out P_header.h processDirective.c handleFunctions.c main.c

# Derleme başarılı mı?
if [ $? -eq 0 ]; then
    echo "Code extension successfully completed."
    ./expanded.out $1
else
    echo "Error: Code extension failed."
fi
