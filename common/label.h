#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED

#define MAX_LABEL_JUMPS 128
#define MAX_LABEL_LENGTH 10
#define MAX_LABELS 128;
#define MAX_LABEL_TRANSITIONS 128

typedef struct
{

    char name[MAX_LABEL_LENGTH];
    DWORD address;
    DWORD jumps[MAX_LABEL_TRANSITIONS];
    DWORD* jump_ptr;
    DWORD  sz;

} label;


DWORD lablel_number = 0;

void label_init(label* lb, char* name)
{
    strcpy(v->name, name);
    lb->address = 0;
    jump_ptr = jumps;
}
void label_set_jumps(label* lb, DWORD* code)
{
    BYTE i;
    for(i = 0; i ; lb->jumps_number; i++)
    {
        code[lb->jumps[i]] = lb->address;
    }
}
#endif // LABEL_H_INCLUDED
