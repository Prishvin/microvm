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

void compile_all(char* input_file, char* ooutput_file);
void compile_file(char* input_file, char* output_file);
BOOL compile_line(char* line, Machine* mac);
BOOL compile_iline(char* line, Machine* mac);
void write_binary(char* filename, Machine* machine);

#endif // COMPILER_H_INCLUDED
