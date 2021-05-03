#ifndef OPCODES_H_INCLUDED
#define OPCODES_H_INCLUDED

#define MAX_OPCODES 20
#include "global.h"
#include <string.h>



typedef struct
{
    DWORD opcode;
    char txt[10];
} Opcode;

Opcode opcodes[MAX_OPCODES];

void initialize_opcodes();
DWORD opcodes_find(char* txt);
#endif // OPCODES_H_INCLUDED
