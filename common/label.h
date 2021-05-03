#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED

#define MAX_LABEL_JUMPS 128
#define MAX_LABEL_LENGTH 10
#define MAX_LABELS 128
#define MAX_LABEL_TRANSITIONS 128


#include "../common/token.h"
#include "../common/machine.h"

#define LABEL_NOT_FOUND 0xFFFF

typedef struct
{

    char name[MAX_LABEL_LENGTH];
    DWORD address;
    DWORD jumps[MAX_LABEL_TRANSITIONS];
    DWORD* jump_ptr;
    DWORD jump_number;
    DWORD  sz;

} label;


label progam_labels[MAX_LABELS];
label* label_ptr;




DWORD lablel_number = 0;

void label_init(label* lb, char* name, DWORD addr)
{
    strcpy(lb->name, name);
    lb->address = addr;
    lb->jump_ptr = lb->jumps;
    lb->jump_number = 0;
}
label* label_find(char* name)
{
       label* ptr = progam_labels;
       label* result = LABEL_NOT_FOUND;
       while(ptr++<label_ptr)
       {
            if(strcmp(ptr->name, name) == 0)
               result = ptr;
       }
    return result;
}
void label_set_jumps(label* lb)
{
    BYTE i;
    for(i = 0; i < lb->jump_number; i++)
    {
        lb->jumps[i] = lb->address;
    }
}

BOOL label_exists(char* name)
{
    BOOL result = FALSE;
    result = label_find(name)!= LABEL_NOT_FOUND;
    return result;
}
#endif // LABEL_H_INCLUDED
