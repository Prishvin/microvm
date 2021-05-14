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
    errno = 0;

    if(argc == 2)
    {
        if(strcmp(argv[1],CLI_FLAG_HELP) == 0)
        {
            printf("Compile file: stackcompiler -c source_file destination_file\n");
            printf("Run:  stackcompiler -r filename\n");
        }
        if(strcmp(argv[1],CLI_FLAG_INTERPRETER) == 0)
        {
            printf("StackVM v0.2.2: welcome.\n");
            printf("Data width: %d.\n", sizeof(DWORD));
            machine_initialize(&machine);
            machine.mode = MACHINE_MODE_INTERPRETER;

            printf("Ready %c\n>",CLI_CMD_CHAR1);
            while ((read = getline(&line, &len, stdin) != -1))
            {

                str_trim_all(line);

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
            machine.mode = MACHINE_MODE_RUN;
            DWORD *ptr = machine.program_ptr;
            DWORD op;
            DWORD qt = opcodes_find("QUIT");
            while(TRUE)
            {
                op = *machine.program_ptr;
                if(op>=qt || *ptr>=machine.memory_end)
                {
                    if(op==qt)
                    {
                        printf("[SUCCESS] program executed.\n");
                        printf("Press any key to quit\n");
                        getchar();
                        exit(0);
                    }
                    else
                    {
                        errno = EDESTADDRREQ;
                        perror("[FATAL] Abnormal termination");
                        getchar();
                        exit(errno);
                    }
                    break;
                }
                if(machine.stack_ptr - machine.machine_stack >= opcodes[*machine.program_ptr].sz )
                    (opcodes[*machine.program_ptr].ptr)();
                else
                {
                    perror("[FATAL] segmentation fault");
                    errno =EILSEQ;
                    getchar();
                    exit(errno);
                }

                //bp();
                machine.program_ptr++;
            }
        }
    }
    if(argc == 4)
    {
        if(strcmp(argv[1],CLI_FLAG_COMPILE) == 0)
        {
            machine.mode = MACHINE_MODE_COMPILER;
            if(compile_all(argv[2], argv[3]))
            {
                printf("[SUCCESS] program compiled to %s\n", argv[3]);
            }
            else
            {
                errno = EINVAL;
                printf("[FAIL] compilation of %s failed\n", argv[2]);
            }
        }
        else
        {
            errno = EINVAL;
            perror("Unknown command");
        }
        getchar();
    }
    return (errno);
}
