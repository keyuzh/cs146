#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>

int main(int argc, char* argv[], char* envp[])
{
    char* globalTrash = getenv("TRASH");
    if (globalTrash != NULL)
    {
        printf("DEFINED: %s\n", globalTrash);
    }
    char localTrash[_POSIX_PATH_MAX];
    getcwd(localTrash, sizeof(localTrash));

    strcat(localTrash, "/.trash");
    printf("TRASH: %s\n", localTrash);
    mkdir(localTrash);

    int i;
    char* fileToTrash;
    char fileLocationInTrash[_POSIX_PATH_MAX];
    for (i = 1; i < argc; i++)
    {
        fileToTrash = argv[i];
        strcpy(fileLocationInTrash, localTrash);
        strcat(fileLocationInTrash, "/");
        strcat(fileLocationInTrash, fileToTrash);
        
        printf("F: %s\n", fileLocationInTrash);
        rename(fileToTrash, fileLocationInTrash);
    }
}