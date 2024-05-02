#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void path() {
	// Get the current working directory
	char cwd[1024]; 
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working directory: %s\n", cwd);

		// Open/create file path.txt for writing
		FILE *file = fopen("path.txt", "w"); // file in write mode
		if(file != NULL) {
			fprintf(file, "Current working directory: %s\n", cwd);
			fclose(file); // close the file
			printf("Current working directory saved to path.txt\n");
		}
		else { // If opening the file failed, print fail message
			printf("Failed to create or open path.txt\n");
		}
	}
	else { // If getting current working directory failed, print fail message
		printf("Failed to get current working directory\n");
	}
}

int main() {
	path();

	return 0;
}

