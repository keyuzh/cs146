#define _XOPEN_SOURCE 500  // need this for nftw(3) to work
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "helper.h"

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    // remove(3) calls unlink(2) for files and rmdir(2) for directories
    return remove(fpath);
}

int main(int argc, char* argv[], char* envp[])
{
    char* globalTrash = getTrashEnvp();
    FILE* trashList = openGlobalTrash(globalTrash, "r");
    while (feof(trashList) == 0)
    {
        // read each line on global trash list and delete the whole dir
        char* line = processLine(trashList);
        if(nftw(line, fn, 4, FTW_DEPTH | FTW_PHYS) && errno != ENOENT)
        {
            // something wrong when traversing the dir, and its not that the dir
            // does not exist (we can ignore that)
            perror("trash");
        }
        free(line);
    }
    fclose(trashList);
    // truncate the content since we no longer need it
    truncate(globalTrash, 0);
}
