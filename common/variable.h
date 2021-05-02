#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED

#define MAX_VARIABLE_LINKS 128
#include "../StackCompiler/src/token.h"

typedef struct {

DWORD links[MAX_VARIABLE_LINKS];
DWORD* link_ptr;
DWORD  sz;
char name[MAX_OPCODE_STR_LENGTH];

} variable;

void var_init(variable* v, char* name)
{
    strcpy(v->name, name);
    v->link_ptr = v->links;
}
void var_set_links(variable* v, DWORD* code, DWORD** code_ptr)
{

}

void var_allocate_space(variable* v, DWORD* code)
{
}

#endif // VARIABLE_H_INCLUDED
