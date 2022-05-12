#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>

#include "helper.h"

int main(int argc, char* argv[], char* envp[])
{
    char* globalTrash = getTrashEnvp();
    char* localTrash = malloc(_POSIX_PATH_MAX + 1);
    getLocalTrash(localTrash);

    int i;
    for (i = 1; i < argc; i++)
    {
        moveFromTrash(argv[i], localTrash);
    }
    free(globalTrash);
    free(localTrash);
}
