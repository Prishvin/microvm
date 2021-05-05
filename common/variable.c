#include "variable.h"





void var_init(variable* v, char* name)
{
    strcpy(v->name, name);
    v->link_ptr = v->links;
}
void var_set_links(variable* v, DWORD address, DWORD* code)
{

    DWORD* ptr = v->links;
    do
    {
        code[*ptr] = address;
    }while(ptr++ < v->link_ptr);
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


