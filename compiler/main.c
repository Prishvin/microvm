#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"
#include "../common/opcodes.h"
#include "../common/token.h"
#include "../common//machine.h"
#include "src/cli.h"
#include "src/interpreter.h"

#define MAX_LEN 256

Machine machine;
Machine backup_machine;

int main( int argc, char *argv[] )
{
    char buffer[MAX_LEN];
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    initialize_opcodes();
    if(argc == 2)
    {
        if(strcmp(argv[1],CLI_FLAG_HELP) == 0)
        {
            printf("Compile file: stackcompiler -c source_file destination_file\n");
            printf("Run:  stackcompiler -r filename\n");
        }
        if(strcmp(argv[1],CLI_FLAG_INTERPRETER) == 0)
        {
            printf("StackVM v0.1: welcome.\n");
            machine_initialize(&machine);
            printf("Ready %c\n>",CLI_CMD_CHAR1);
            while ((read = getline(&line, &len, stdin) != -1))
            {
                if(*line == CLI_CMD_CHAR1)
                {
                    process_interpreter_command(line);
                }
                else
                {
                    process_interpeter_opcode(line);

                }
            }
        }


    }
    if(argc == 3)
    {

        if(strcmp(argv[1],CLI_READ) == 0)
        {
            machine_initialize(&machine);
            machine_load(argv[2], &machine);
            DWORD *ptr = machine.program_ptr;
            DWORD op;
            DWORD qt = opcodes_find("QUIT");
            while(TRUE)
            {
                op = *machine.program_ptr;
                if(op>=qt || *ptr>=machine.memory_end)
                {
                    if(op==qt )
                    {
                        perror("[SUCCESS] program executed.");
                    }
                    else
                    {
                        perror("[FATAL] Abnormal termination");

                    }
                    break;
                }
                (opcodes[*machine.program_ptr].ptr)();
                //bp();
                machine.program_ptr++;
            }
        }
    }
    if(argc == 4)
    {
        if(strcmp(argv[1],CLI_FLAG_COMPULE) == 0)
        {
            if(compile_all(argv[2], argv[3]))
            {
                printf("[SUCCESS] program compiled to %s\n", argv[3]);
            }
            else
            {
                 printf("[FAIL] compilation of %s failed\n", argv[2]);
            }
        }

        else
            perror("Unknown command");


           getchar();
    }
}
