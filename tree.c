#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void execute_tree() {
    if (mkdir("Dir0", 0755) == -1) {    // created a directory called Dir0
        perror("Failed to create Dir0");
        return;
    }

      if (chdir("Dir0") == -1) {
        perror("Failed to change directory to Dir0");
        return;
    }

    // we have created the empty directory Dir1 inside dir0
    if (mkdir("Dir1", 0755) == -1) {
        perror("Failed to create Dir1");
        chdir("..");
        return; 
    }

    printf("Directories 'Dir0' and 'Dir0/Dir1' created successfully.\n");
}

int main() {
    execute_tree();
    return 0;
}