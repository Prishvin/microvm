#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"
#include "../common/opcodes.h"
#include "../common/token.h"
#include "../common//machine.h"

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
        if(strcmp(argv[1],"-h") == 0)
        {
            printf("Compile file: stackcompiler -c source_file destination_file\n");
            printf("Run:  stackcompiler -r filename\n");
        }
        if(strcmp(argv[1],"-i") == 0)
        {

            machine_initialize(&machine);
            printf("Ready\n>");
            while ((read = getline(&line, &len, stdin) != -1))
            {
                if(*line == '$')
                {
                    str_trim(line, '\n');
                    str_shift_left(line, sizeof(line), 1 );
                    if(strcmp(line, "reset") == 0)
                    {
                        machine_initialize(&machine);
                    }
                    if(strcmp(line, "stack") == 0)
                    {   BYTE i = 1;
                        printf("Stack memory, bytes N=%d\n", machine.stack_ptr - machine.machine_stack);
                        DWORD* ptr = machine.machine_stack;
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
                    if(strcmp(line, "mem") == 0)
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

                    if(strcmp(line, "var") == 0)
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

                    if(strcmp(line, "labels") == 0)
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
                        machine.program_ptr = ptr;
                        (opcodes[*ptr].ptr)();
                        printf("OK");
                    }
                    else
                        printf("Error");
                }
                printf("\n>");
            }
        }


    }
    if(argc == 3)
    {
        if(strcmp(argv[1],"-r") == 0)
        {
            Machine interpreter;
            machine_initialize(&interpreter);
            machine_load(argv[2], &interpreter);
            //TODO READ WORD
        }
    }
    if(argc == 4)
    {
        if(strcmp(argv[1],"-c") == 0)
            compile_all(argv[2], argv[3]);
        else
            perror("Unknown command");
    }
}
