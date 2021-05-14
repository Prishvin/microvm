#ifndef OPCODES_H_INCLUDED
#define OPCODES_H_INCLUDED

#define MAX_OPCODES 100
#include "global.h"
#include "machine.h"
#include <string.h>
#include "token.h"

DWORD PUSHOP;

typedef void (* voidfunc)(void);

typedef struct
{
    BYTE sz;
    DWORD opcode;
    voidfunc ptr;
    char txt[10];
} Opcode;

Opcode opcodes[MAX_OPCODES];

void initialize_opcodes();
DWORD opcodes_find(char* txt);
#endif // OPCODES_H_INCLUDED
