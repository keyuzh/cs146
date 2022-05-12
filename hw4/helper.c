// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <getopt.h>
#include <limits.h>
// #include <errno.h>

#include "helper.h"

void reportError(const char* msg)
{
    perror(msg);
    exit(1);
}

void getLocalTrash(char* localTrash)
{
    getcwd(localTrash, _POSIX_PATH_MAX);
    strcat(localTrash, "/.trash");
}

char* getTrashEnvp()
{
    char* globalTrash = getenv("TRASH");
    if (globalTrash == NULL)
    {
        reportError("trash: TRASH environment variable not defined");
    }
    int length = strlen(globalTrash) + 1;
    if (globalTrash[0] == '~')
    {
        // if '~' is found in $TRASH, replace it with $HOME
        char* home = getenv("HOME");
        length += strlen(home) - 1;
        char* trash = malloc(length);
        strcpy(trash, home);
        strcpy(&trash[strlen(home)], &globalTrash[1]);
        return trash;
    }
    char* trash = malloc(length);
    return strcpy(trash, globalTrash);
}
