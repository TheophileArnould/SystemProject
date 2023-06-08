#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100

void printArguments(char* args[]) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("Argument %d: %s\n", i, args[i]);
    }
}

void changeDirectory(char* path) {
    if (chdir(path) == 0) {
        getcwd(path,MAX_COMMAND_LENGTH);
        printf("Directory changed to: %s\n", path);
    } else {
        fprintf(stderr, "Failed to change directory to: %s\n", path);
    }
}

void changeStandarO(char* pathStandarOI){
    int fd;
    if ((fd = open(pathStandarOI, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
    {
        fprintf(stderr, "Failed to open document : %s\n",pathStandarOI);
    }else{
        dup2(fd, 1);   // make stdout go to file
        //dup2(fd, 2);   // make stderr go to file - you may choose to not do this

        close(fd);     // fd no longer needed - the dup'ed handles are sufficient
    }
    

    

}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char* args[MAX_COMMAND_LENGTH / 2 + 1];  // +1 for NULL terminator

    while (1) {
        printf("Shell> ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        // Remove newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Exit if "exit" command is entered
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Tokenize the command
        char* token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                // Input redirection
                token = strtok(NULL, " ");
                int fileDescriptor = open(token, O_RDONLY);
                dup2(fileDescriptor, STDIN_FILENO);
                close(fileDescriptor);
                token = strtok(NULL, " ");
                continue;
            }
            
            args[i] = token;
            token = strtok(NULL, " ");
            i++;

        }
        args[i] = NULL;
        if(strcmp(args[0], "cd") == 0){
            if (args[1] != NULL) {
                changeDirectory(args[1]);
            } else {
                fprintf(stderr, "cd: Missing argument.\n");
            }
        }
        else{
            
            // Fork a child process
            pid_t pid = fork();

            if (pid < 0) {
                fprintf(stderr, "Failed to fork a child process.\n");
                return 1;
            } else if (pid == 0) {
                // Child process
                
                execvp(args[0], args);
                
                fprintf(stderr, "Failed to execute the command.\n");
                return 1;
            } else {
                // Parent process
                wait(NULL);
            }
        }
    }

    return 0;
}
