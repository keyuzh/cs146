#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>

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


int main(int argc, char* argv[], char* envp[])
{
    char* globalTrash = getenv("TRASH");
    if (globalTrash == NULL)
    {
        reportError("srm: TRASH environment variable not defined");
    }
    // make local trash directory
    char localTrash[_POSIX_PATH_MAX];
    getLocalTrash(&localTrash);
    if (mkdir(localTrash, -1) && errno != EEXIST)
    {
        // mkdir fails 
        // and errno is not EEXIST (which is ignored)
        reportError("srm: Failed to create local trash directory");
    }

    FILE* trashList = fopen(globalTrash, "a");
    fputs(localTrash, trashList);
    fputc('\n', trashList);
    fclose(trashList);

    int i;
    char* fileToTrash;
    char fileLocationInTrash[_POSIX_PATH_MAX];
    for (i = 1; i < argc; i++)
    {
        fileToTrash = argv[i];
        strcpy(fileLocationInTrash, localTrash);
        strcat(fileLocationInTrash, "/");
        strcat(fileLocationInTrash, fileToTrash);
        
        // printf("F: %s\n", fileLocationInTrash);
        rename(fileToTrash, fileLocationInTrash);
    }
}
