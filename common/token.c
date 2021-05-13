#include "token.h"

char token_control[9][MAX_OPCODE_STR_LENGTH] = {"CALL", "JGE", "JLE", "JG", "JL", "JNE", "JE", "JMP",""};
char token_memory[7][MAX_OPCODE_STR_LENGTH] =  {"FRMM", "TOMM", "AFROM", "ATOM", "PTRTO", "TOPTR", ""};

char token_push[2][MAX_OPCODE_STR_LENGTH] =  {"PUSH", ""};

#define TOKEN_UNKNOWN 0xFFFF

BOOL token_unknown(DWORD token)
{

    return TOKEN_UNKNOWN == token;
}
BOOL string_in_array(char** arr, char* str)
{
    BYTE i;
    for(i = 0;**(arr + i); i++)
        if(strcmp(**(arr + i), str)==0)
            return TRUE;

    return FALSE;
}
BOOL token_is_print(char* token)
{
    return strcmp(token, "PRINT") == 0;
}
BOOL token_is_dup(char* token)
{
    return strcmp(token, "DUP") == 0;
}
BOOL    token_is_comment(char* token)
{
    return *token == COMMENT_CHAR;
}

BOOL    token_is_label(char* token)
{
    return *token == LABEL_CHAR;
}

BOOL    token_is_var(char* token)
{
    return strcmp(token, VAR_STR)==0;
}
BOOL    token_is_control(char* token)
{
    return str_in_array(token_control, token);
}
BOOL    token_is_mem(char* token)
{
    return str_in_array(token_memory, token);

}
BOOL    token_is_array(char* token)
{
    return FALSE;

}
BOOL    token_is_push(char* token)
{
    return str_in_array(token_push, token);

}
