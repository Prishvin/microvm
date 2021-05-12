#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include "global.h"
#include <string.h>

#define COMMENT_CHAR '#'
#define LABEL_CHAR ':'
#define VAR_STR "VAR"

#define TOKEN_UNKNOWN 0xFFFF

char token_control[9][MAX_OPCODE_STR_LENGTH];
char token_memory[5][MAX_OPCODE_STR_LENGTH];
char token_push[2][MAX_OPCODE_STR_LENGTH];



BOOL token_unknown(DWORD token);
BOOL string_in_array(char** arr, char* str);
BOOL token_is_dup(char* token);
BOOL    token_is_comment(char* token);

BOOL    token_is_label(char* token);

BOOL    token_is_var(char* token);
BOOL    token_is_control(char* token);
BOOL    token_is_mem(char* token);
BOOL    token_is_array(char* token);
BOOL    token_is_push(char* token);
BOOL    token_is_print(char* token);

#endif // TOKEN_H_INCLUDED
