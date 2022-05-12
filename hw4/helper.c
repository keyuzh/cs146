#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

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

char* getTrashEnvp(char* currentCmd)
{
    char* globalTrash = getenv("TRASH");
    if (globalTrash == NULL)
    {
        fprintf(stderr, "%s: TRASH environment variable not defined", currentCmd);
        exit(1);
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

FILE* openGlobalTrash(char* filepath, char* mode)
{
    FILE* f = fopen(filepath, mode);
    if (filepath == NULL)
    {
        reportError("failed to open file at $TRASH environment variable");
    }
    return f;
}

char* processLine(FILE* f)
{
    char* line = NULL;
    size_t lineLen;
    getline(&line, &lineLen, f);
    // remove \n at the end
    line[strlen(line)-1] = 0;
    return line;
}

char* makeFileLocationInTrash(char* localTrash, char* fileToTrash)
{
    char* fileLocationInTrash = malloc(_POSIX_PATH_MAX + 1);
    strcpy(fileLocationInTrash, localTrash);
    strcat(fileLocationInTrash, "/");
    strcat(fileLocationInTrash, fileToTrash);
}

void moveFromTrash(char* fileToTrash, char* localTrash)
{
    char* fileLocationInTrash = makeFileLocationInTrash(localTrash, fileToTrash);
    if (rename(fileLocationInTrash, fileToTrash))
    {
        perror(fileToTrash);
    }
}

void moveToTrash(char* fileToTrash, char* localTrash)
{
    char* fileLocationInTrash = makeFileLocationInTrash(localTrash, fileToTrash);
    if(rename(fileToTrash, fileLocationInTrash))
    {
        perror(fileToTrash);
    }
}

char* makeLocalTrash()
{
    char* localTrash = malloc(_POSIX_PATH_MAX);
    getLocalTrash(localTrash);
    // make local trash directory
    if (mkdir(localTrash, -1) && errno != EEXIST)
    {
        // mkdir fails 
        // and errno is not EEXIST (which is ignored)
        reportError("srm: Failed to create local trash directory");
    }
    return localTrash;
}

void addLocalTrashToGlobal(char* localTrash, char* globalTrash)
{
    // add local trash dir to global trash file for later use by "trash"
    FILE* trashList = openGlobalTrash(globalTrash, "a");
    fputs(localTrash, trashList);
    fputc('\n', trashList);
    fclose(trashList);
}
