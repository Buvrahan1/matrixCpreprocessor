//TEST
#include <stdio.h>

int main() {
    // Declare arrays
    @int A(7, 3)
    @int B(3, 3)
    @int C(3, 3)
    @int D(3)
    @int E(3)
    @int F(3)
    
    // Initialize arrays
    @init A = 1
    @init B = 2
    @init D = 3
    @init E = 4
    
    // Print initialized arrays
    @print A
    @print B
    @print D
    @print E
    
    // Perform array operations
    @copy C = A
    @print C
    
    // Matrix multiplication
    @mmult C = A * B
    @print C
    
    // Vector addition
    @add F = D + E
    @print F
    
    // Dot product
    @dotp F = D . E
    
    // Read array from file
    @read A < input.txt
    
    // Sum of elements
    @sum A
    
    // Average of elements
    @aver B
    
    return 0;
}
