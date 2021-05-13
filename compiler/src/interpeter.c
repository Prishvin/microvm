#include "interpreter.h"



void process_interpreter_command(char* line)
{

                    DWORD sz = strlen(line);
                    str_shift_left(line,sz , 1 );
                     str_trim(line, '\n');

                    if(strcmp(line, CLI_FLAGS) == 0)
                    {
                        printf("Flag Equal = %d\nFlag Greater = %d\n>", machine.flag_eq, machine.flag_gr);
                    }
                    else if(strcmp(line, CLI_BACKUP) == 0)
                    {
                        memcpy(&backup_machine,&machine, sizeof(machine));
                    }

                    else if(strcmp(line, CLI_RESTORE) == 0)
                    {
                         memcpy(&machine, &backup_machine, sizeof(machine));
                    }
                     else if(strcmp(line, CLI_CLEAR) == 0)
                    {
                        clrscr();
                    }
                     else if(strcmp(line, CLI_RESET) == 0)
                    {
                        machine_initialize(&machine);
                        clrscr();
                    }
                     else if(strcmp(line, CLI_STACK) == 0)
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
                     else if(strcmp(line, CLI_MEM) == 0)
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

                     else if(strcmp(line, CLI_VAR) == 0)
                    {

                        printf("Program variables, N=%d\n", machine.var_number);
                        printf("Variables memory start, [ADDRESS]=%d\n", machine.variable_memory);
                        variable* ptr = machine.variables;
                        BYTE i = 0;
                        while(ptr<machine.variable_ptr)
                        {
                            variable v;

                            printf("[name]=%s, [Addr] = 0x%02X, [VAL] = 0x%02X\n", ptr->name, ptr->address, machine.variable_memory[i]);
                            ptr++;
                            i++;
                        }
                    }

                     else if(strcmp(line, CLI_LABELS) == 0)
                    {
                        printf("Program labels, N=%d\n", machine.lablel_number);

                        for (int i = 0; i < machine.lablel_number; i++)
                        {
                            printf("[Name]= %s, [ADDRESS]=%02X, [Jumps]=%d", machine.progam_labels[i].name, machine.progam_labels[i].address,  machine.progam_labels[i].jump_number  );
                        }
                    }
                    else
                    {
                        perror("[FATAL] interpreter command not found");
                    }
}

void process_interpeter_opcode(char* line)
{
    DWORD *ptr = machine.program_ptr;
                    DWORD op;
                    if(strlen(line)>MIN_INPUT_LENGTH && compile_line(line, &machine))
                    {
                        machine.program_ptr=ptr;
                        op=*ptr;
                        (opcodes[op].ptr)();
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
