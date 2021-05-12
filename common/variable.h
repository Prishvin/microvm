#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED


#include "token.h"
#include "machine.h"







void var_init(variable* v, char* name);
void var_set_links(variable* v, DWORD address, DWORD* code);

void var_allocate_space(variable* v, DWORD* code);

variable* variable_find(char* name, variable* variables, DWORD index, variable* last);
#endif // VARIABLE_H_INCLUDED
