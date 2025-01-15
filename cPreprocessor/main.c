#include "P_header.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct ArrayTable AT[MAX_ARRAYS];
int atCount = 0;
struct ParseTable PT;
FILE *outputFile;

int main(int argc, char *argv[]) {
    // Komut satırından dosya adını al
    if (argc != 2) {
        fprintf(stderr, "Kullanım: %s <dosya_adi>\n", argv[0]);
        return 1;
    }

    // Kullanıcının belirttiği dosya adını al
    char *fileName = argv[1];

    FILE *inputFile = fopen(fileName, "r");
    if (!inputFile) {
        perror("Unable to open input file");
        return 1;
    }

    outputFile = fopen("expanded.c", "w");
    if (!outputFile) {
        perror("Unable to open output file");
        fclose(inputFile);
        return 1;
    }

    char line[1024];
    char *trimmedLine;

    while (fgets(line, sizeof(line), inputFile)) {
        trimmedLine = line;
        while (isspace((unsigned char)*trimmedLine)) trimmedLine++;
        if (*trimmedLine == '@') {
            processDirective(trimmedLine);
        } else {
            fputs(trimmedLine, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
