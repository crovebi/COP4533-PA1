# COP4533-PA1
Programming Assignment 1: Matching and Verifying by Sebastian Crovetto (51487318) &amp; Mosimiloluwa Ajani (79157785)
## Instructions for compilation
In the COP4533-PA1 folder, run the commands:
g++ src/matcher.cpp -o matcher
g++ src/verifier.cpp -o verifier
To build the executable for the matcher and verifier respectively.

There is also the testing exe: *random_input_generator* which is made by running
g++ tests/random_input_generator.cpp -o random

The random input generator takes in a command line input for the number of hospitals/students and inputs a random permutation of preferences into *input&period;in*.

To execute the respective exe, run the commands from the same folder:
matcher.exe
verifier.exe
random.exe (number of hospitals/students)

## I/O information
The I/O files are stored in the *data* folder. *input&period;in* stores the input for *matcher.exe*.
*output&period;out* stores the output for *matcher.exe* and is also what *verifier.exe* attempts to verify.

To edit the parameters for the executables, simply change *input&period;in* to another valid data set and run *matcher.exe*.
The output can be ran through *verifier.exe* to obtain the new verification.

## Part C: Graphs and analysis
