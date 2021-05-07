#include "label.h"




DWORD lablel_number = 0;

void label_init(label* lb, char* name, DWORD addr)
{
    strcpy(lb->name, name);
    lb->address = addr;
    lb->jump_ptr = lb->jumps;
    lb->jump_number = 0;

}
label* label_find(char* name, label* labels, label* last)
{
       label* ptr = labels;
       label* result = LABEL_NOT_FOUND;
       do
       {
            if(strcmp(ptr->name, name) == 0)
               result = ptr;
       }while(ptr++<last)
       ;
    return result;
}
void label_set_jumps(label* lb)
{
    BYTE i;
    for(i = 0; i < lb->jump_number; i++)
    {
        machine.machine_memory[lb->jumps[i]] = lb->address;
        printf("jump %d <- %d address %d\n", lb->jumps[i], lb->address, i);
    }
}

BOOL label_exists(char* name, label* labels, label* last)
{
    BOOL result = FALSE;
    result = label_find(name, labels, last)!=(label*) LABEL_NOT_FOUND;
    return result;
}
