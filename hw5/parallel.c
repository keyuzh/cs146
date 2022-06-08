#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "parallel.h"

char* getCommand()
{
    char* command = NULL;
    size_t len = 0;
    if (getline(&command, &len, stdin) == -1) 
    {
        // EOF
        free(command);
        return NULL;
    }
    return command;
}

void startCommand(char* shell, char* command, unsigned int* running)
{
    char* args[] = {
        shell,
        "-c",
        command,
        NULL
    };
    pid_t pid;
    if ((pid = fork()) < 0) 
    {
        // error handling in case fork fails
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) // child
    {
        int exec_result = execvp(args[0], args);
        if (exec_result < 0) {  
            exit(EXIT_FAILURE);  // error handling
        }
    }
    else // parent
    {
        // increment counter of running children
        ++(*running);
    }
}

int processCommand(bool* finished, char* shell, unsigned int* running)
{
    char* command = getCommand();
    if (command == NULL)
    {
        *finished = true;  // less command than N
        return -1;
    }
    startCommand(shell, command, running);
    free(command);  // cleanup
    return 0;
}


int main(int argc, char* argv[], char* envp[])
{
    char* shell = getenv("SHELL");
    unsigned int n = sysconf(_SC_NPROCESSORS_ONLN);  // number of CPUs
    unsigned int running = 0;
    unsigned int exit_code = 0;  
    bool finished = false;
    // parse arguments
    if (argc > 1)
    {
        unsigned int nth_arg = -1;
        if (strcmp(argv[1], "-s") == 0)
        {
            // -s specified
            shell = argv[2];
            nth_arg = 3;
        }
        else 
        {
            nth_arg = 1;
        }
        if (argc > nth_arg)
        {
            n = atoi(argv[nth_arg]);
        }
    }
    // read command lines from stdin
    size_t i;
    for (i = 0; i < n; i++)
    {
        if (processCommand(&finished, shell, &running)) {break;}
    }
    // reap child then start new command (if needed)
    while (running)
    {
        // wait for child
        int exit_status;
        pid_t child_pid = wait(&exit_status);
        --running;
        if (exit_status != 0)
        {
            // child exited error
            ++exit_code;
        }
        // start new command if there's more
        if (!finished) {processCommand(&finished, shell, &running);}
    }
    // max exit code is 255
    exit_code = exit_code > 255 ? 255 : exit_code;
    exit(exit_code);
}
