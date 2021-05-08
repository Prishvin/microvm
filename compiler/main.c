#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"
#include "../common/opcodes.h"
#include "../common/token.h"
#include "../common//machine.h"
#include "src/cli.h"
#define MAX_LEN 256

Machine machine;

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
            printf("StackVM v0.1: buy me a bear if you used it\n");
            machine_initialize(&machine);
            printf("Ready\n>");
            while ((read = getline(&line, &len, stdin) != -1))
            {
                if(*line == CLI_CMD_CHAR)
                {
                    str_trim(line, '\n');
                    str_shift_left(line, sizeof(line), 1 );
                    if(strcmp(line, CLI_FLAGS) == 0)
                    {
                        printf("Flag Equal = %d\nFlag Greater = %d\n>", machine.flag_eq, machine.flag_gr);
                    }
                    if(strcmp(line, CLI_CLEAR) == 0)
                    {
                        clrscr();
                    }
                    if(strcmp(line, CLI_RESET) == 0)
                    {
                        machine_initialize(&machine);
                        clrscr();
                    }
                    if(strcmp(line, CLI_STACK) == 0)
                    {
                        BYTE i = 1;
                        printf("Stack memory %d bytes\n>", machine.stack_ptr - machine.stack_first);
                        DWORD* ptr = machine.stack_first;
                        while(ptr<machine.stack_ptr)
                        {
                            printf("0x%02X ", *ptr);
                            if(i%4 == 0)
                                printf("\n");
                            ptr++;
                            i++;
                        }
                        printf("\n");
                    }
                    if(strcmp(line, CLI_MEM) == 0)
                    {
                        printf("Program memory, bytes N=%d\n", machine.program_ptr - machine.machine_memory);
                        for (int i = 0; i < machine.program_ptr - machine.machine_memory; i++)
                        {
                            printf("0x%02X ", machine.machine_memory[i]);
                            if(i%4 == 0)
                                printf("\n");
                        }
                        printf("\n");
                    }

                    if(strcmp(line, CLI_VAR) == 0)
                    {

                        printf("Program variables, N=%d\n", machine.var_number);
                        variable* ptr = machine.variables;
                        while(ptr<machine.variable_ptr)
                        {
                            variable v;

                            printf("[name]=%s, [Addr] = 0x%02X, [VAL] = 0x%02X\n", ptr->name, ptr->address, *ptr->address);
                            ptr++;
                        }

                    }

                    if(strcmp(line, CLI_LABELS) == 0)
                    {
                        printf("Program labels, N=%d\n", machine.lablel_number);
                        for (int i = 0; i < machine.lablel_number; i++)
                        {
                            printf("[Name]= %s, [ADDRESS]=%02X, [Jumps]=%d", machine.progam_labels[i].name, machine.progam_labels[i].address,  machine.progam_labels[i].jump_number  );
                        }
                    }
                }
                else
                {

                    DWORD *ptr = machine.program_ptr;
                    if(compile_line(line, &machine))
                    {
                        machine.program_ptr=ptr;

                        (opcodes[*ptr].ptr)();
                        DWORD result = 0xFFFF;
                        if(machine.stack_ptr < machine.stack_end)
                            result = *(machine.stack_ptr-1);
                        printf("=%d\n>", result);

                    }
                    else
                    {
                        printf("\n>");
                    }

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
            DWORD op = *ptr;
            DWORD qt = opcodes_find("QUIT");
            while(TRUE)
            {
                if(op>=qt || *ptr>=machine.memory_end)
                {
                    if(op ==qt )
                    {
                        perror("[SUCCESS] program executed.");
                    }
                    else
                    {
                        perror("[FATAl] Abnormal termination");

                    }
                    break;
                }

                (opcodes[*ptr].ptr)();
                ptr++;

            }
        }
    }
    if(argc == 4)
    {
        if(strcmp(argv[1],CLI_FLAG_COMPULE) == 0)
            compile_all(argv[2], argv[3]);
        else
            perror("Unknown command");
    }
}
