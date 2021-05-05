#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED


#include <string.h>
#include "../common/token.h"
#include "../common/machine.h"

#define LABEL_NOT_FOUND (label*) 0xFFFF








void label_init(label* lb, char* name, DWORD addr);
label* label_find(char* name, label* labels, label* last);
void label_set_jumps(label* lb);

BOOL label_exists(char* name, label* labels, label* last);
#endif // LABEL_H_INCLUDED
