#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "helper.h"

int main(int argc, char* argv[], char* envp[])
{
    char* globalTrash = getTrashEnvp();
    char* localTrash = makeLocalTrash();
    addLocalTrashToGlobal(localTrash, globalTrash);

    int i;
    for (i = 1; i < argc; i++)
    {
        moveToTrash(argv[i], localTrash);
    }
    free(localTrash);
    free(globalTrash);
}
