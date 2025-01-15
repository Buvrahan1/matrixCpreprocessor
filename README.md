# matrixCpreprocessor

C Preprocessor for Matrix Operations
Project Overview
This project is a custom C Preprocessor designed to enhance C programming by introducing additional functionality for handling matrix operations. The preprocessor interprets specific directives in a given C program and expands them into executable C code, enabling seamless manipulation of 1D and 2D arrays.

Key Features
Matrix Operations:
Addition, dot product, and matrix multiplication for 1D and 2D arrays.
Reduction Operations:
Summation and average calculation of array elements.
Directive-Based Operations:
Declare, initialize, read, copy, and print arrays through preprocessor commands.
Automatic Code Generation:
Expands directives into valid C code and saves the output as expanded.c.
Shell Automation:
Includes a shell script (P232) to automate preprocessing and compilation.
How It Works
The preprocessor parses the input C program for custom directives (e.g., @int, @add, @dotp).
These directives are translated into standard C code using the implemented functions.
The expanded C code is saved to a new file (expanded.c), ready for compilation and execution.
Preprocessor Directives
The following custom directives are supported:

Declaration: Declares arrays with dimensions.
Example: @int A(3,5)
Initialization: Sets all elements to a specific value.
Example: @init A = 2
Arithmetic Operations: Performs addition or multiplication.
Example: @add C = A + B
Reduction: Calculates the sum or average of array elements.
Example: @sum A, @aver A
Utility: Reads from files, prints arrays, and copies array data.
Example: @read A < file1, @print A

Usage
Write your C program with the custom directives.
Run the provided shell script with your input file:

./P232 myCprog.c

The expanded C code will be generated in expanded.c.
Project Structure
P_header.h: Header file containing global variables for preprocessor operations.
processDirective.c: Main logic for parsing and expanding directives.
handleFunctions.c: Implements functionality for matrix operations.
main.c: Entry point for the program.
P232: Shell script to automate the process.
Goals
The primary goal of this project is to provide an efficient way to perform matrix and array operations in C programming, abstracting complex code into simple, high-level directives.

Requirements
Compiler: GCC
Platform: Linux environment
Dependencies: No external libraries required

How to Run
Navigate to the project directory:
cd repository-name

Use the shell script to process your input file:
./P232 example.c

License
This project is open-source and available under the MIT License.
