#ifndef HELPERS_H
#define HELPERS_H

void reportError(const char* msg);
void getLocalTrash(char* localTrash);
char* getTrashEnvp();
FILE* openGlobalTrash(char* filepath, char* mode);
char* processLine(FILE* f);
char* makeFileLocationInTrash(char* localTrash, char* fileToTrash);
void moveFromTrash(char* fileToTrash, char* localTrash);
void moveToTrash(char* fileToTrash, char* localTrash);
char* makeLocalTrash();
void addLocalTrashToGlobal(char* localTrash, char* globalTrash);

#endif
