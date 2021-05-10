#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../common/global.h"
#include "../../common/auxillary.h"
#include "../../common/opcodes.h"
#include "../../common/token.h"
#include "../../common//machine.h"
#include "cli.h"
#define MAX_LEN 256

void process_interpreter_command(char* line);

void process_interpeter_opcode(char* line);

#endif // INTERPRETER_H_INCLUDED
