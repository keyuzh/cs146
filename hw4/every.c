#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "every.h"

void setOption(num* op, char* op_str)
{
    char* option = op_str + 1;
    char* end;
    op->n = strtol(option, &end, 10);
    if (*end != 0)
    {
        op->m = strtol(end+1, NULL, 10);
    }
}

void printNextLine(FILE* f)
{
    // need to use calloc or valgrind complains
    char* line = calloc(100, sizeof(char));
    size_t n = 100 * sizeof(char);
    getline(&line, &n, f);
    printf("%s", line);
    free(line);
}

void skipLine(FILE* f)
{
    char c;
    do
    {
        c = fgetc(f);
    } while (c != '\n' && c != EOF);
}

void checkOption(num* op)
{
    // no need to check < 0 since they are unsigned
    if ((op->n == 0) || (op->m > op->n))
    {
        fprintf(stderr, "every: illegal option. N,M must satisfy N > 0, M >= 0, and M <= N\n");
        exit(1);
    }
}

void process(FILE* f, num* op)
{
    int currentLine = 0;
    while (feof(f) == 0)
    {
        if (currentLine % op->n < op->m)
        {
            printNextLine(f);
        }
        else
        {
            skipLine(f);
        }
        ++currentLine;
    }
}

int main(int argc, char* argv[], char* envp[])
{
    // default
    num op = {1,1};
    int files_arg = 1;
    // parse args
    if (argc > 1 && argv[1][0] == '-')
    {
        // -N,M option given
        setOption(&op, argv[1]);
        files_arg = 2;
    }
    else
    {
        // not given, search envp
        char* option = getenv("EVERY");
        if (option != NULL)
        {
            setOption(&op, option);
        }
    }
    // check m, n
    checkOption(&op);
    if (files_arg >= argc)
    {
        // no file given, use stdin
        process(stdin, &op);
        return 0;
    }
    int i;
    for (i = files_arg; i < argc; i++)
    {
        FILE* f = fopen(argv[i], "r");
        if (f == NULL)
        {
            perror("every: failed to open file");
            continue;
        }
        process(f, &op);
        fclose(f);
    }
    return 0;
}
