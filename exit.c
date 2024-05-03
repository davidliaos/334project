#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>   
#include <sys/stat.h> 

void list_directory_contents() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char *file_type;

    if ((dir = opendir(".")) == NULL) {
        perror("opendir() error");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &file_stat); 
        if (S_ISDIR(file_stat.st_mode)) file_type = "Directory";
        else if (S_ISREG(file_stat.st_mode)) file_type = "Regular file";
        else file_type = "Other";

        printf("%10s %ld %s\n", file_type, file_stat.st_size, entry->d_name);
    }

    closedir(dir);
}

void exit() {
    
    printf("Recent commands:\n");

    printf("\nCurrent directory contents:\n");
    list_directory_contents();  

    
    printf("\nPress RETURN to exit...\n");
    getchar();  
    exit(0);
}

