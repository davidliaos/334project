// exit.c - Implements the 'exit' command for the custom shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// this function executes the 'exit' command
void execute_exit() {
    
    printf("Recent commands:\n");

    // Print detailed list of all content in the directory that the command use is in
    printf("\nCurrent directory contents:\n");
    system("ls -l");  // uses the  'ls -l' command to list directory contents

    // waits for "return" to be press
    printf("\nPress RETURN to exit...\n");
    getchar();  // Wait for user input

    // gets out of the shell
    exit(0);
}

int main() {
    execute_exit();
    return 0;
}
