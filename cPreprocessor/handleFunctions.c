#include "P_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleDeclaration() {
    strcpy(AT[atCount].name, PT.lhs);
    if (PT.rhs2[0] != '\0') {
        AT[atCount].dim = 2;
        strcpy(AT[atCount].size1, PT.rhs1);
        strcpy(AT[atCount].size2, PT.rhs2);
        fprintf(outputFile, "    int %s[%s][%s];\n", PT.lhs, PT.rhs1, PT.rhs2);
    } else {
        AT[atCount].dim = 1;
        strcpy(AT[atCount].size1, PT.rhs1);
        AT[atCount].size2[0] = '\0';
        fprintf(outputFile, "    int %s[%s];\n", PT.lhs, PT.rhs1);
    }
    atCount++;
}

void handleRead() {
    fprintf(outputFile, "    FILE *file = fopen(\"%s\", \"r\");\n", PT.rhs1);
    fprintf(outputFile, "    for (int i = 0; i < %s; ++i) {\n", AT[atCount - 1].size1);
    fprintf(outputFile, "        fscanf(file, \"%%d\", &%s[i]);\n", PT.lhs);
    fprintf(outputFile, "    }\n");
    fprintf(outputFile, "    fclose(file);\n");
}

void handleCopy() {
    int dim_lhs = 0, dim_rhs = 0;
    int size1_lhs = 0, size2_lhs = 0;
    int size1_rhs = 0, size2_rhs = 0;

    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            dim_lhs = AT[i].dim;
            size1_lhs = atoi(AT[i].size1);
            if (dim_lhs == 2) {
                size2_lhs = atoi(AT[i].size2);
            }
        }

        if (strcmp(AT[i].name, PT.rhs1) == 0) { 
            dim_rhs = AT[i].dim;
            size1_rhs = atoi(AT[i].size1);
            if (dim_rhs == 2) {
                size2_rhs = atoi(AT[i].size2);
            }
        }
    }
   

    if (dim_lhs == 1 && dim_rhs == 1) {

        fprintf(outputFile, "    for (int i = 0; i < %d; ++i)\n", size1_lhs);
        fprintf(outputFile, "        %s[i] = %s[i];\n", PT.lhs, PT.rhs1);
    } else if (dim_lhs == 2 && dim_rhs == 2) {

        fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1_lhs);
        fprintf(outputFile, "        for (int j = 0; j < %d; ++j)\n", size2_lhs);
        fprintf(outputFile, "            %s[i][j] = %s[i][j];\n", PT.lhs, PT.rhs1);
        fprintf(outputFile, "    }\n");
    } else {
        // Error: Unsupported copy operation
        printf("Error: Unsupported copy operation.\n");
    }
}


void handleInitialize() {
    int dim = 0;
    int size1 = 0, size2 = 0;
    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            dim = AT[i].dim;
            size1 = atoi(AT[i].size1);
            if (dim == 2) {
                size2 = atoi(AT[i].size2);
            }
            break;
        }
    }

    if (dim == 1) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i)\n", size1);
        fprintf(outputFile, "        %s[i] = %s;\n", PT.lhs, PT.rhs1);
    } else if (dim == 2) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1);
        fprintf(outputFile, "        for (int j = 0; j < %d; ++j)\n", size2);
        fprintf(outputFile, "            %s[i][j] = %s;\n", PT.lhs, PT.rhs1);
        fprintf(outputFile, "    }\n");
    }
}


void handlePrint() {
    int dim = 0;
    int size1 = 0, size2 = 0;
    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            dim = AT[i].dim;
            size1 = atoi(AT[i].size1);
            if (dim == 2) {
                size2 = atoi(AT[i].size2);
            }
            break;
        }
    }
    if (dim == 1) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i)\n", size1);
        fprintf(outputFile, "        printf(\"%%d \", %s[i]);\n", PT.lhs);
    } else if (dim == 2) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1);
        fprintf(outputFile, "        for (int j = 0; j < %d; ++j)\n", size2);
        fprintf(outputFile, "            printf(\"%%d \", %s[i][j]);\n", PT.lhs);
        fprintf(outputFile, "       printf(\"\\n\");\n");
        fprintf(outputFile, "    }\n");
    }
    fprintf(outputFile, "    printf(\"\\n\");\n");
}


void handleDotProduct() {
    int size_A = 0, size_B = 0;

    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.rhs1) == 0) {
            size_A = atoi(AT[i].size1);
        }
        if (strcmp(AT[i].name, PT.rhs2) == 0) {
            size_B = atoi(AT[i].size1);
        }
    }

    if (size_A != size_B) {
        printf("Dot product error: incompatible dimensions.\n");
        return;
    }

    fprintf(outputFile, "    int P_dot = 0;\n");
    fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size_A);
    fprintf(outputFile, "        P_dot += %s[i] * %s[i];\n", PT.rhs1, PT.rhs2);
    fprintf(outputFile, "    }\n");
}


void handleAddition() {
    int dim_lhs = 0, dim_rhs1 = 0, dim_rhs2 = 0;
    int size1_lhs = 0, size2_lhs = 0;
    int size1_rhs1 = 0, size2_rhs1 = 0;
    int size1_rhs2 = 0, size2_rhs2 = 0;

    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            dim_lhs = AT[i].dim;
            size1_lhs = atoi(AT[i].size1);
            if (dim_lhs == 2) {
                size2_lhs = atoi(AT[i].size2);
            }
        }
        if (strcmp(AT[i].name, PT.rhs1) == 0) {
            dim_rhs1 = AT[i].dim;
            size1_rhs1 = atoi(AT[i].size1);
            if (dim_rhs1 == 2) {
                size2_rhs1 = atoi(AT[i].size2);
            }
        }
        if (strcmp(AT[i].name, PT.rhs2) == 0) {
            dim_rhs2 = AT[i].dim;
            size1_rhs2 = atoi(AT[i].size1);
            if (dim_rhs2 == 2) {
                size2_rhs2 = atoi(AT[i].size2);
            }
        }
    }

    if (dim_lhs != dim_rhs1 || dim_lhs != dim_rhs2) {
        printf("Addition error: incompatible dimensions.\n");
        return;
    }

    if (dim_lhs == 1) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i)\n", size1_lhs);
        fprintf(outputFile, "        %s[i] = %s[i] + %s[i];\n", PT.lhs, PT.rhs1, PT.rhs2);
    } else if (dim_lhs == 2) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1_lhs);
        fprintf(outputFile, "        for (int j = 0; j < %d; ++j)\n", size2_lhs);
        fprintf(outputFile, "            %s[i][j] = %s[i][j] + %s[i][j];\n", PT.lhs, PT.rhs1, PT.rhs2);
        fprintf(outputFile, "    }\n");
    }
}


void handleMatrixMultiplication() {
    int size1_A = 0, size2_A = 0, size1_B = 0, size2_B = 0, size1_C = 0, size2_C = 0;
    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.rhs1) == 0) {
            size1_A = atoi(AT[i].size1);
            size2_A = atoi(AT[i].size2);
        }
        if (strcmp(AT[i].name, PT.rhs2) == 0) {
            size1_B = atoi(AT[i].size1);
            size2_B = atoi(AT[i].size2);
        }
        if (strcmp(AT[i].name, PT.lhs) == 0){
            size1_C = atoi(AT[i].size1);
            size2_C = atoi(AT[i].size2);
        }
    }
    if (size2_A != size1_B) {
        printf("Matrix multiplication error: incompatible dimensions.\n");
        return;
    }


    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            strcpy(AT[i].size1, PT.rhs1);
            strcpy(AT[i].size2, PT.rhs2);
            break;
        }
    }

    fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1_C);
    fprintf(outputFile, "        for (int j = 0; j < %d; ++j) {\n", size2_C);
    fprintf(outputFile, "            %s[i][j] = 0;\n", PT.lhs);
    fprintf(outputFile, "            for (int k = 0; k < %d; ++k) {\n", size2_A);
    fprintf(outputFile, "                %s[i][j] += %s[i][k] * %s[k][j];\n", PT.lhs, PT.rhs1, PT.rhs2);
    fprintf(outputFile, "            }\n");
    fprintf(outputFile, "        }\n");
    fprintf(outputFile, "    }\n");
}


void handleSum() {
    int dim = 0;
    int size1 = 0, size2 = 0;

    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            dim = AT[i].dim;
            size1 = atoi(AT[i].size1);
            if (dim == 2) {
                size2 = atoi(AT[i].size2);
            }
            break;
        }
    }

    fprintf(outputFile, "    int P_sum = 0;\n");

    if (dim == 1) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i)\n", size1);
        fprintf(outputFile, "        P_sum += %s[i];\n", PT.lhs);
    } else if (dim == 2) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1);
        fprintf(outputFile, "        for (int j = 0; j < %d; ++j)\n", size2);
        fprintf(outputFile, "            P_sum += %s[i][j];\n", PT.lhs);
        fprintf(outputFile, "    }\n");
    }
}

void handleAverage() {
    int dim = 0;
    int size1 = 0, size2 = 0;

    for (int i = 0; i < atCount; ++i) {
        if (strcmp(AT[i].name, PT.lhs) == 0) {
            dim = AT[i].dim;
            size1 = atoi(AT[i].size1);
            if (dim == 2) {
                size2 = atoi(AT[i].size2);
            }
            break;
        }
    }

    fprintf(outputFile, "    int P_aver = 0;\n");

    if (dim == 1) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i)\n", size1);
        fprintf(outputFile, "        P_aver += %s[i];\n", PT.lhs);
        fprintf(outputFile, "    P_aver /= %d;\n", size1);
    } else if (dim == 2) {
        fprintf(outputFile, "    for (int i = 0; i < %d; ++i) {\n", size1);
        fprintf(outputFile, "        for (int j = 0; j < %d; ++j)\n", size2);
        fprintf(outputFile, "            P_aver += %s[i][j];\n", PT.lhs);
        fprintf(outputFile, "    }\n");
        fprintf(outputFile, "    P_aver /= (%d * %d);\n", size1, size2);
    }
}

