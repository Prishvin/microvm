#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"
#include "../common/opcodes.h"
#include "../common/token.h"
#include "../common//machine.h"
#include "src/cli.h"
#include "src/interpreter.h"
#include "src/test.h"

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
    if(argc == 2) // -h help, -i interpreter,
    {
        if(strcmp(argv[1],CLI_FLAG_HELP) == 0)
        {
            printf("Compile file: stackcompiler -c source_file destination_file\n");
            printf("Run:  stackcompiler -r filename\n");
        }
        if(strcmp(argv[1],CLI_FLAG_INTERPRETER) == 0)
        {
            printf("StackVM %s: welcome.\n", VERSION);
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

        if(strcmp(argv[1],CLI_TEST) == 0)
        {
          run_test(argv[2]);
        }
        if(strcmp(argv[1],CLI_READ) == 0)
        {
          run_binary(argv[2], TRUE);
        }

        if(strcmp(argv[1],CLI_RUN) == 0)
        {
            char binary[256]= "binary.b";
            if(compile_to_binary(argv[2], binary) == RESULT_OK)
                run_binary(binary, TRUE);
        }
    }
    if(argc == 4)
    {
        if(strcmp(argv[1],CLI_FLAG_COMPILE) == 0)
        {
            compile_to_binary(argv[2], argv[3]);
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
