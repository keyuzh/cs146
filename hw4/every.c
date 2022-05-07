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

int main(int argc, char* argv[], char* envp[])
{
    // default
    num op = {1,1};
    int files_arg = 1;
    // parse args
    if (argc > 1 && argv[1][0] == '-')
    {
        // -N,M option given
        printf("given\n");
        setOption(&op, argv[1]);
        printf("N, M = %ld, %ld\n", op.n, op.m);
        files_arg = 2;
    }
    else
    {
        printf("not given\n");
        // not given, search envp
        char* option = getenv("EVERY");
        if (option != NULL)
        {
            setOption(&op, option);
            printf("FOUND envp, NM = %ld, %ld\n", op.n, op.m);
        }
    }
    int i;
    printf("FIles:\n");
    for (i = files_arg; i < argc; i++)
    {
        FILE* f = fopen(argv[i], "r");
        int currentLine = 0;
        while (feof(f) == 0)
        {
            // printf("C: %d, %d\n", currentLine, currentLine%op.n);
            if (currentLine % op.n < op.m)
            {
                printNextLine(f);
            }
            else
            {
                skipLine(f);
            }
            ++currentLine;
        }
        fclose(f);
    }
}
