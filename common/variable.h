#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED

#define MAX_VARIABLE_LINKS 128
#include "token.h"
#include "machine.h"
#define VARIABLE_NOT_FOUND 0xFFFF
#define VARIABLE_MEMORY_SIZE 512


typedef struct {

DWORD links[MAX_VARIABLE_LINKS];
DWORD* link_ptr;
DWORD  sz;
char name[MAX_OPCODE_STR_LENGTH];

} variable;



variable progam_variables[VARIABLE_MEMORY_SIZE];
variable* variable_ptr;
DWORD var_number;

void var_init(variable* v, char* name)
{
    strcpy(v->name, name);
    v->link_ptr = v->links;
}
void var_set_links(variable* v, DWORD address, DWORD* code)
{
    BYTE i;
    i = 1;
    DWORD* ptr = v->links;
    while(ptr++ < v->link_ptr)
    {
        code[*ptr] = address;
    }
}

void var_allocate_space(variable* v, DWORD* code)
{
}

variable* variable_find(char* name)
{
       variable* ptr = progam_variables;
       variable* result = VARIABLE_NOT_FOUND;
       while(ptr++<variable_ptr)
       {
            if(strcmp(ptr->name, name) == 0)
               result = ptr;
       }
    return result;
}
#endif // VARIABLE_H_INCLUDED
