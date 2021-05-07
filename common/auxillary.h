#ifndef AUXILLARY_H_INCLUDED
#define AUXILLARY_H_INCLUDED

#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

typedef struct list_node_t node;
struct list_node_t
{
    DWORD index;
    DWORD value;
    DWORD argument;
    node* left;
    node* right;
    node* childs[MAX_REFERENCES];
    DWORD nchilds;

};

void node_init(node* ptr, node* l, node* r, DWORD i, DWORD arg);
char** str_split(BYTE* ntokens, char* a_str, const char a_delim);
BOOL str_in_array(char (*arr)[MAX_OPCODE_STR_LENGTH], char* str);
void str_to_upper(char * temp);
char str_is_number(char *text);
BOOL is_numeric(char* name, DWORD* number);
void str_shift_left(char myarray[], int sz, int shiftBy);
void str_trim(char* str, char c);

#endif // AUXILLARY_H_INCLUDED
