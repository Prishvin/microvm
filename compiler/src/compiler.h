#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../../common/global.h"
#include "../../common/auxillary.h"
#include "../../common/opcodes.h"
#include "../../common/token.h"
#include "../../common//machine.h"

#define MAX_LEN 256
#define MAX_CONSTANTS 128
#define MAX_PREPROCESSOR_NAME_LEN 128

#define PRE_INCLUDE "include"
#define PRE_DEFINE "define"


#define CHAR_CONSTANT '_'
typedef struct {

 char source[MAX_PREPROCESSOR_NAME_LEN];
 char destination[MAX_PREPROCESSOR_NAME_LEN];
 DWORD value;

} constant;

constant constants[MAX_CONSTANTS];

int nconstants;
BOOL compile_all(char* input_file, char* ooutput_file);
void compile_file(char* input_file, char* output_file);
BOOL compile_line(char* line, Machine* mac);
BOOL preprocessor(char* line, Machine* mac);
///  return: FALSE is token is a constant, but not found in list. TRUE otherwise
BOOL preprocessor_substitute(char* token);
BOOL compile_iline(char* line, Machine* mac);
constant* constant_find(char* name, int* index);
void write_binary(char* filename, Machine* machine);

#endif // COMPILER_H_INCLUDED
