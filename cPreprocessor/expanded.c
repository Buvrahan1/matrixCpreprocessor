#include <stdio.h>
int main() {
// Declare arrays
    int A[7][3];
    int B[3][3];
    int C[3][3];
    int D[3];
    int E[3];
    int F[3];
// Initialize arrays
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; ++j)
            A[i][j] = 1;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            B[i][j] = 2;
    }
    for (int i = 0; i < 3; ++i)
        D[i] = 3;
    for (int i = 0; i < 3; ++i)
        E[i] = 4;
// Print initialized arrays
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; ++j)
            printf("%d ", A[i][j]);
       printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            printf("%d ", B[i][j]);
       printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 3; ++i)
        printf("%d ", D[i]);
    printf("\n");
    for (int i = 0; i < 3; ++i)
        printf("%d ", E[i]);
    printf("\n");
// Perform array operations
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            C[i][j] = A[i][j];
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            printf("%d ", C[i][j]);
       printf("\n");
    }
    printf("\n");
// Matrix multiplication
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    for (int i = 0; i < 0; ++i) {
        for (int j = 0; j < 0; ++j)
            printf("%d ", C[i][j]);
       printf("\n");
    }
    printf("\n");
// Vector addition
    for (int i = 0; i < 3; ++i)
        F[i] = D[i] + E[i];
    for (int i = 0; i < 3; ++i)
        printf("%d ", F[i]);
    printf("\n");
// Dot product
    int P_dot = 0;
    for (int i = 0; i < 3; ++i) {
        P_dot += D[i] * E[i];
    }
// Read array from file
    FILE *file = fopen("input.txt", "r");
    for (int i = 0; i < 3; ++i) {
        fscanf(file, "%d", &A[i]);
    }
    fclose(file);
// Sum of elements
    int P_sum = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; ++j)
            P_sum += A[i][j];
    }
// Average of elements
    int P_aver = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            P_aver += B[i][j];
    }
    P_aver /= (3 * 3);
return 0;
}
