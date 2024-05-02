// list.c - Implements the 'list' command for the custom shell

#include <stdio.h>
#include <stdlib.h>

// Function to execute the 'list' command
void execute_list() {
    // Clear the terminal screen using ANSI escape sequences
    printf("\033[H\033[J"); // Clears the screen

    // Execute 'ls -l' command to list detailed directory contents
    // and simultaneously write the output to 'tree.txt'
    system("ls -l | tee tree.txt");
}
