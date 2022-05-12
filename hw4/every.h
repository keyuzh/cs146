#ifndef EVERY_H
#define EVERY_H

typedef struct num
{
    unsigned long m;
    unsigned long n;
} num;

void setOption(num* op, char* op_str);
void printNextLine(FILE* f);
void skipLine(FILE* f);
void checkOption(num* op);
void process(FILE* f, num* op);

#endif
