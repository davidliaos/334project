#include <dirent.h>   
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <string.h>   
#include <unistd.h>   

void list() {
    DIR *d;
    struct dirent *dir;
    struct stat statbuf;
    char currentPath[1024];
    char filePath[1024 + 256]; 
    FILE *fp;

    printf("\033[H\033[J");

    if (getcwd(currentPath, sizeof(currentPath)) == NULL) {
        perror("Error getting current directory");
        return;
    }

    d = opendir(currentPath);
    if (d == NULL) {
        perror("Error opening directory");
        return;
    }

    fp = fopen("tree.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        closedir(d);
        return;
    }

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        snprintf(filePath, sizeof(filePath), "%s/%s", currentPath, dir->d_name);

        if (stat(filePath, &statbuf) == -1) {
            perror("Error getting file status");
            continue;
        }

       
        printf("%10ld %s\n", statbuf.st_size, dir->d_name);
        fprintf(fp, "%10ld %s\n", statbuf.st_size, dir->d_name);
    }

    fclose(fp);
    closedir(d);
}