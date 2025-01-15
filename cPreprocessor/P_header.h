#ifndef P_HEADER_H
#define P_HEADER_H

#include <stdio.h>

#define MAX_ARRAYS 20

struct ArrayTable {
    char name[10];
    int dim;
    char size1[10];
    char size2[10];
};

struct ParseTable {
    char oper[10];
    char lhs[10];
    char rhs1[10];
    char rhs2[10];
};

extern struct ArrayTable AT[MAX_ARRAYS];
extern int atCount;
extern struct ParseTable PT;
extern FILE *outputFile;

void processDirective(char *directive);
void handleDeclaration();
void handleRead();
void handleCopy();
void handleInitialize();
void handlePrint();
void handleDotProduct();
void handleAddition();
void handleMatrixMultiplication();
void handleSum();
void handleAverage();

#endif // P_HEADER_H
