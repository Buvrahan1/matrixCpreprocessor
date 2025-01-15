#include "P_header.h"
#include <string.h>
#include <ctype.h>


void strtrim(char *str) {
    int len = strlen(str);
    int start = 0, end = len - 1;

    // Baştaki boşlukları atar
    while (isspace((unsigned char)str[start])) {
        start++;
    }

    // Sondaki boşlukları atar
    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    // Yeni son karakterin ardından null karakteri ekler
    str[end + 1] = '\0';

    // Başlangıçtan sona kadar olan kısmı kaydırır
    if (start > 0) {
        memmove(str, str + start, end - start + 2);
    }
}

void processDirective(char *directive) {
    directive++;
    char *token = strtok(directive, " ");
    strcpy(PT.oper, token);

    if (strcmp(PT.oper, "int") == 0) {
        token = strtok(NULL, "(");
        strtrim(token);
        strcpy(PT.lhs, token);
        token = strtok(NULL, ")");
        if (strchr(token, ',')) {
            sscanf(token, "%[^,],%s", PT.rhs1, PT.rhs2);
            strtrim(PT.rhs1);
            strtrim(PT.rhs2);
        } else {
            strcpy(PT.rhs1, token);
            strtrim(PT.rhs1);
            PT.rhs2[0] = '\0';
        }
    } else if (strcmp(PT.oper, "read") == 0 || strcmp(PT.oper, "print") == 0 || strcmp(PT.oper, "sum") == 0 || strcmp(PT.oper, "aver") == 0) {
        token = strtok(NULL, " ");
        strtrim(token);
        strcpy(PT.lhs, token);
        token = strtok(NULL, " ");
        if (token && strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            if (token) {
                strcpy(PT.rhs1, token);
                strtrim(PT.rhs1);
            }
        }
        PT.rhs2[0] = '\0';
    } else if (strcmp(PT.oper, "mmult") == 0 || strcmp(PT.oper, "dotp") == 0 || strcmp(PT.oper, "add") == 0) {
        token = strtok(NULL, " ");
        strtrim(token);
        strcpy(PT.lhs, token);
        token = strtok(NULL, " ");
        if (strcmp(token, "=") == 0) {
            token = strtok(NULL, " ");
            strtrim(token);
            strcpy(PT.rhs1, token);
            token = strtok(NULL, " ");
            while (token != NULL) {
                if (isalpha(token[0])) {
                    strcat(PT.rhs2, token);
                }
                token = strtok(NULL, " ");
            }
            strtrim(PT.rhs2);
        } else {
            PT.rhs1[0] = '\0';
            PT.rhs2[0] = '\0';
        }
    } else {
        token = strtok(NULL, " ");
        strtrim(token);
        strcpy(PT.lhs, token);
        token = strtok(NULL, " ");
        if (strcmp(token, "=") == 0) {
            token = strtok(NULL, " ");
            strtrim(token);
            strcpy(PT.rhs1, token);
            token = strtok(NULL, " ");
            if (token) {
                strcpy(PT.rhs2, token);
                strtrim(PT.rhs2);
            } else {
                PT.rhs2[0] = '\0';
            }
        } else {
            PT.rhs1[0] = '\0';
            PT.rhs2[0] = '\0';
        }
    }
    strtrim(PT.lhs);
    strtrim(PT.rhs1);
    strtrim(PT.rhs2);
    
    if (strcmp(PT.oper, "int") == 0) {
        handleDeclaration();
    } else if (strcmp(PT.oper, "read") == 0) {
        handleRead();
    } else if (strcmp(PT.oper, "copy") == 0) {
        handleCopy();
    } else if (strcmp(PT.oper, "init") == 0) {
        handleInitialize();
    } else if (strcmp(PT.oper, "print") == 0) {
        handlePrint();
    } else if (strcmp(PT.oper, "dotp") == 0) {
        handleDotProduct();
    } else if (strcmp(PT.oper, "add") == 0) {
        handleAddition();
    } else if (strcmp(PT.oper, "mmult") == 0) {
        handleMatrixMultiplication();
    } else if (strcmp(PT.oper, "sum") == 0) {
        handleSum();
    } else if (strcmp(PT.oper, "aver") == 0) {
        handleAverage();
    }
}
