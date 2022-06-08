#ifndef PARALLEL_H
#define PARALLEL_H
#include <stdbool.h>

char* getCommand();
void startCommand(char* shell, char* command, unsigned int* running);
int processCommand(bool* finished, char* shell, unsigned int* running);

#endif
