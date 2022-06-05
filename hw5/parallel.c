#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

char* getCommand()
{
    char* command = NULL;
    size_t len = 0;
    if (getline(&command, &len, stdin) == -1) 
    {
        // EOF
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
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) // child
    {
        int exec_result = execvp(args[0], args);
        if (exec_result < 0) {  
            exit(EXIT_FAILURE);
        }
    }
    else // parent
    {
        ++(*running);
    }
}

int main(int argc, char* argv[], char* envp[])
{
    char* shell = getenv("SHELL");
    unsigned int n = sysconf(_SC_NPROCESSORS_ONLN);

    unsigned int running = 0;
    unsigned int exit_code = 0;  
    bool finished = false;


    printf("shell: %s; n: %d\n", shell, n);

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
    
    printf("shell: %s; n: %d\n", shell, n);

    // read command lines from stdin
    // while (1)
    for (size_t i = 0; i < n; i++)
    {
        char* command = getCommand();
        if (command == NULL)
        {
            finished = true;
            break;
        }
        startCommand(shell, command, &running);
    }

    while (running)
    {
        // wait for child
        int exit_status;
        pid_t child_pid = wait(&exit_status);
        --running;
        if (exit_status != 0)
        {
            printf("status: %d\n", WIFEXITED(exit_status));
            ++exit_code;
        }

        // start new command if there's more
        if (!finished)
        {
            char* command = getCommand();
            if (command == NULL)
            {
                finished = true;
                continue;
            }
            startCommand(shell, command, &running);
        }
    }
    exit_code = exit_code > 255 ? 255 : exit_code;
    printf("CODE: %d\n", exit_code);
    exit(exit_code);
}