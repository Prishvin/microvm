#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#define MAX_REFERENCES 64
#define MAX_OPCODE_STR_LENGTH 10
#include <string.h>
#include <ctype.h>

typedef  unsigned char BYTE;
typedef  unsigned int DWORD;
typedef unsigned long long QWORD;
typedef unsigned char BOOL;

#define NULL 0

#define VARIABLE_NOT_FOUND 0xFFFF
#define VARIABLE_MEMORY_SIZE 512
#define MAX_VARIABLE_LINKS 128
#define MAX_LABEL_JUMPS 128
#define MAX_LABEL_LENGTH 10
#define MAX_LABELS 128
#define MAX_LABEL_TRANSITIONS 128

#define HARVARD
#define TRACE_VM

#define MIN_INPUT_LENGTH 1

struct varvar {

DWORD index;
DWORD* address;
DWORD links[MAX_VARIABLE_LINKS];
DWORD* link_ptr;
DWORD  sz;
char name[MAX_OPCODE_STR_LENGTH];

} ;

typedef struct varvar variable;

typedef struct
{

    char name[MAX_LABEL_LENGTH];
    DWORD address;
    DWORD jumps[MAX_LABEL_TRANSITIONS];
    DWORD* jump_ptr;
    DWORD jump_number;
    DWORD  sz;

} label;



#define  TRUE 1
#define  FALSE 0

#endif // GLOBAL_H_INCLUDED
