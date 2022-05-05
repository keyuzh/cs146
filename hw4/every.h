#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

typedef struct num
{
    unsigned long m;
    unsigned long n;
} num;

void setOption(num* op, char* op_str);
