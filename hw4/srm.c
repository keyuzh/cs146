#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include "helper.h"

void moveToTrash(const char* fileToTrash, const char* localTrash)
{
    char fileLocationInTrash[_POSIX_PATH_MAX];
    strcpy(fileLocationInTrash, localTrash);
    strcat(fileLocationInTrash, "/");
    strcat(fileLocationInTrash, fileToTrash);
    // printf("F: %s\n", fileLocationInTrash);
    rename(fileToTrash, fileLocationInTrash);
}

int main(int argc, char* argv[], char* envp[])
{
    // get global trash from envp
    // char* globalTrash = getenv("TRASH");
    // if (globalTrash == NULL)
    // {
    //     reportError("srm: TRASH environment variable not defined");
    // }
    char* globalTrash = getTrashEnvp();
    // make local trash directory
    char* localTrash = malloc(_POSIX_PATH_MAX);
    getLocalTrash(localTrash);
    if (mkdir(localTrash, -1) && errno != EEXIST)
    {
        // mkdir fails 
        // and errno is not EEXIST (which is ignored)
        reportError("srm: Failed to create local trash directory");
    }
    // add local trash dir to global trash file for later use by "trash"
    FILE* trashList = fopen(globalTrash, "a");
    fputs(localTrash, trashList);
    fputc('\n', trashList);
    fclose(trashList);

    int i;
    for (i = 1; i < argc; i++)
    {
        moveToTrash(argv[i], localTrash);
    }
    free(localTrash);
    free(globalTrash);
}
