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




DWORD var_number;

void var_init(variable* v, char* name)
{
    strcpy(v->name, name);
    v->link_ptr = v->links;
}
void var_set_links(variable* v, DWORD address, DWORD* code)
{

    DWORD* ptr = v->links;
    while(ptr++ < v->link_ptr)
    {
        code[*ptr] = address;
    }
}

void var_allocate_space(variable* v, DWORD* code)
{
}

variable* variable_find(char* name, variable* variables, variable* last)
{
       variable* ptr = variables;
       variable* result = VARIABLE_NOT_FOUND;
       do
       {
            if(strcmp(ptr->name, name) == 0)
               result = ptr;
       }while(ptr++<last)
       ;
    return result;
}
#endif // VARIABLE_H_INCLUDED
