#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void path() {
	char cwd[1024]; 
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working directory: %s\n", cwd);

		FILE *file = fopen("path.txt", "w"); 
		if(file != NULL) {
			fprintf(file, "Current working directory: %s\n", cwd);
			fclose(file); 
			printf("Current working directory saved to path.txt\n");
		}
		else { 
			printf("Failed to create or open path.txt\n");
		}
	}
	else { 
		printf("Failed to get current working directory\n");
	}
}