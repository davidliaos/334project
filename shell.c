#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

extern void execute_tree();
extern void execute_list();
extern void execute_path();
extern void execute_exit();

void handle_sigint(int sig) {
    if (sig == SIGINT) {
        printf("\nInterrupt signal received. Exiting...\n");
        exit(0);
    }
}

void execute_pipe(char *cmd1[], char *cmd2[]) {
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        perror("Failed to create pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(pipe_fds[0]);
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[1]);
        execvp(cmd1[0], cmd1);
        perror("Failed to execute command 1");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(pipe_fds[1]);
        dup2(pipe_fds[0], STDIN_FILENO);
        close(pipe_fds[0]);
        execvp(cmd2[0], cmd2);
        perror("Failed to execute command 2");
        exit(EXIT_FAILURE);
    }

    close(pipe_fds[0]);
    close(pipe_fds[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main() {
    signal(SIGINT, handle_sigint);

    char command[256];
    while (1) {
        printf("myshell> ");
        if (!fgets(command, sizeof(command), stdin)) continue;
        command[strcspn(command, "\n")] = '\0';  // Strip newline

        if (strstr(command, "|")) {
            char *cmd1 = strtok(command, "|");
            char *cmd2 = strtok(NULL, "|");
            if (cmd1 && cmd2) {
                char *args1[] = { cmd1, NULL };
                char *args2[] = { cmd2, NULL };
                execute_pipe(args1, args2);
            }
        } else {
            if (strcmp(command, "tree") == 0) {
                execute_tree();
            } else if (strcmp(command, "list") == 0) {
                execute_list();
            } else if (strcmp(command, "path") == 0) {
                execute_path();
            } else if (strcmp(command, "exit") == 0) {
                execute_exit();
            } else {
                printf("Unknown command: %s\n", command);
            }
        }
    }

    return 0;
}
