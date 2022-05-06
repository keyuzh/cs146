#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>

int fn(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    return remove(fpath);
}

int main(int argc, char* argv[], char* envp[])
{
    char* globalTrash = getenv("TRASH");
    // if (globalTrash == NULL)
    // {
    //     reportError("trash: TRASH environment variable not defined");
    // }

    FILE* trashList = fopen(globalTrash, "r");
    while (feof(trashList) == 0)
    {
        char* line = NULL;
        size_t lineLen;
        getline(&line, &lineLen, trashList);
        // remove \n at the end
        line[strlen(line)-1] = 0;
        nftw(line, fn, 4, FTW_DEPTH | FTW_PHYS);
        free(line);
    }
    fclose(trashList);
}