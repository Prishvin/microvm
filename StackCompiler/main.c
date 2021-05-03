#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"
#include "../common/opcodes.h"
#include "../common/token.h"
#include "../common//machine.h"

#define MAX_LEN 256

int main( int argc, char *argv[] )
{
    if( argc == 3 )
    {
        printf("Processing file %s. Binery output to %s\n", argv[1],argv[2]);
    }
    else if( argc > 3 )
    {
        printf("Too many arguments supplied.\n");
    }
    else
    {
        printf("Two arguments expected.\n");
    }

    char** tokens;
    FILE* fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("Failed: ");
        return 1;
    }
    char line[MAX_LEN];
    // -1 to allow room for NULL terminator for really long string
    program_ptr = machine_memory; //now pointer is at first instruction
    variable_ptr = progam_variables;
    label_ptr = progam_labels;
    var_number = 0;
    initialize_opcodes();
 program_ptr = machine_memory;

    while (fgets(line, MAX_LEN - 1, fp))
    {
        // Remove trailing newline
        //buffer[strcspn(buffer, "\n")] = 0;
        printf("%s\n", line);
        BYTE ntokens;
        tokens = str_split(&ntokens, line, ' ');

        if (tokens)
        {
            int i = 0;;
            //for (i = 0; *(tokens + i); i++)
            {
                char* token = *(tokens + i);
                str_to_upper(token);
                if(token_is_comment(token))
                {
                    printf("Comment found =[%s]\n", (char*) line);
                    continue;

                }
                else if(token_is_var(token))
                {
                    if(ntokens == 2)
                    {
                        char* argument = *(tokens + i + 1);
                        var_init(variable_ptr, token);
                        variable_ptr++;
                        var_number++;
                        continue;
                    }
                    if(ntokens == 3)
                    {
                        perror("FATAL: array not implemented yet");
                        continue;
                    }
                    else
                    {
                        perror("FATAL: missing VAR arguments");
                        continue;
                    }
                }
                else if(token_is_label(token))
                {
                str_shift_left(token, sizeof(token), 1);
                    if(!label_exists(token, progam_labels, label_ptr))
                    {
                        label_init(label_ptr++, token,  machine_memory-program_ptr);
                    }
                    label* lb = label_find(token, progam_labels, label_ptr);
                    program_ptr++;
                    continue;
                }
                DWORD op =  opcodes_find(token);
                *program_ptr++ = op;//add opcode if opcode is not var and label

                if(token_unknown(token))
                {
                    perror("FATAL: Unexpected opcode");
                }



                if(token_is_control(token))
                {
                    if(ntokens == 2)
                    {
                        char* argument = *(tokens + i + 1);
                        str_to_upper(argument);
                        if(!label_exists(argument, progam_labels, label_ptr))
                        {
                            label_init(label_ptr++, argument, 0);
                        }
                        label* lb = label_find(argument, progam_labels, label_ptr);
                        *(lb->jump_ptr++) = machine_memory-program_ptr;
                        lb->jump_number++;
                        *program_ptr++ = 0; // label address will be garbage at thi point. label adress to be set after progam is compiled
                    }
                    else
                    {
                        perror("FATAL: no argument supplied");
                    }
                }
                else if(token_is_mem(token))
                {
                    if(ntokens == 2)
                    {
                        char* argument = *(tokens + i + 1);
                        DWORD number;
                        if(is_numeric(argument, &number))
                        {
                            *program_ptr++=number;
                        }
                        else
                        {
                            variable* var = variable_find(argument, progam_variables, variable_ptr);
                            if((DWORD) var == VARIABLE_NOT_FOUND)
                            {
                                perror("FATAL: variable not found");
                            }
                            else
                            {
                                *(var->link_ptr++) =machine_memory-program_ptr;
                                *program_ptr++ = 0;
                            }

                        }
                    }
                    else
                    {
                        perror("FATAL: no argument supplied");
                    }
                }

                else if(token_is_dup(token))
                {
                    if(ntokens == 1)
                        *program_ptr++ = 1;
                    if(ntokens == 2)
                    {
                        char* argument = *(tokens + i + 1);
                        DWORD number;
                        if(is_numeric(argument, &number))
                        {
                            *program_ptr++ = number;
                        }
                    }

                }

                *program_ptr++ = opcodes_find("QUIT");


                free(token);
            }
            printf("\n");
            free(tokens);
        }
    }

    BYTE i;
    for(i = 0; i < lablel_number; i++)
        label_set_jumps(&progam_labels[i]);

    for(i = 0; i < var_number; i++)
    {
        var_set_links(&progam_variables[i],(DWORD) (program_ptr - machine_memory), machine_memory);
        *program_ptr++ = 0;
    }

    fclose(fp);
     return 0;
    }
