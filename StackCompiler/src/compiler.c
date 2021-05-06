#include "compiler.h"
#include<stdio.h>
#include<stdlib.h>


void write_binary(char* filename, Machine* mac)
{
    DWORD i;
    FILE* fout=fopen(filename,"wb");
    if(fout !=NULL)
    {

        fwrite(mac->machine_memory, sizeof(DWORD), mac->program_ptr - mac->machine_memory, fout );

    }
    fclose(fout);
}
void compile_file(char* input_file, char* output_file)
{

}
void compile_line(char* line, Machine* mac)
{
    printf("[Processing line]\n %s", line);
        char** tokens;
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
                return;

            }
            else if(token_is_var(token))
            {
                if(ntokens == 2)
                {
                    char* argument = *(tokens + i + 1);
                    var_init(mac->variable_ptr, argument);
                    mac->variable_ptr++;
                    mac->var_number++;
                    return;
                }
                if(ntokens == 3)
                {
                    perror("FATAL: array not implemented yet");
                    return;
                }
                else
                {
                    perror("FATAL: missing VAR arguments");
                    return;
                }
            }
            else if(token_is_label(token))
            {
                str_shift_left(token, sizeof(token), 1);
                if(!label_exists(token, mac->progam_labels, mac->label_ptr))
                {
                    label_init(mac->label_ptr++, token,  mac->machine_memory-mac->program_ptr);
                    mac->lablel_number++;
                }
                label* lb = label_find(token, mac->progam_labels, mac->label_ptr);
                lb->address = mac->program_ptr-mac->machine_memory;

                printf("Label ptr =%d\n", mac->program_ptr - mac->machine_memory);

                mac->program_ptr++;

                return;
            }
            DWORD op =  opcodes_find(token);
            printf("%s [PTR]=%d\n", token, mac->program_ptr - mac->machine_memory);
            *mac->program_ptr++ = op;//add opcode if opcode is not var and label

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
                    if(!label_exists(argument, mac->progam_labels, mac->label_ptr))
                    {
                        label_init(mac->label_ptr++, argument, 0);
                        mac->lablel_number++;
                    }
                    label* lb = label_find(argument, mac->progam_labels, mac->label_ptr);
                    *(lb->jump_ptr++) = mac->machine_memory-mac->program_ptr;
                    lb->jump_number++;
                    printf("Label %s ptr =%d\n", argument,  mac->program_ptr - mac->machine_memory);
                    *mac->program_ptr++ = 0; // label address will be garbage at thi point. label adress to be set after progam is compiled
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
                        printf("Numberic argument %s\n [PTR] =%d\n", argument,  mac->program_ptr - mac->machine_memory);
                        *mac->program_ptr++=number;
                    }
                    else
                    {
                        variable* var = variable_find(argument, mac->variables,  mac->variable_ptr);
                        if((DWORD) var == VARIABLE_NOT_FOUND)
                        {
                            perror("FATAL: variable not found");
                        }
                        else
                        {
                            printf("Link argument %s ptr =%d\n", argument,  mac->program_ptr - mac->machine_memory);
                            *(var->link_ptr++) =mac->program_ptr - mac->machine_memory;
                            *mac->program_ptr++ = 0;
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
                {
                    printf("Dup ptr =%d\n",  mac->program_ptr - mac->machine_memory);
                    *mac->program_ptr++ = 1;
                }
                if(ntokens == 2)
                {
                    char* argument = *(tokens + i + 1);
                    DWORD number;
                    if(is_numeric(argument, &number))
                    {
                        printf("Dup ptr =%d\n",  mac->program_ptr - mac->machine_memory);
                        *mac->program_ptr++ = number;
                    }
                }

            }



            free(token);
        }
        printf("\n");
        free(tokens);
    }
}
void compile_all(char* input_file, char* ooutput_file)
{

    FILE* fp;
    fp = fopen(input_file, "r");
    if (fp == NULL)
    {
        perror("Failed: ");
        return 1;
    }
    char line[MAX_LEN];
    // -1 to allow room for NULL terminator for really long string
    machine.program_ptr = machine.machine_memory; //now pointer is at first instruction
    machine.variable_ptr = machine.variables;
    machine.label_ptr = machine.progam_labels;

    initialize_opcodes();
    machine.program_ptr = machine.machine_memory;

    while (fgets(line, MAX_LEN - 1, fp))
    {
        compile_line(line, &machine);
    }
    printf("QUIT ptr =%d\n",  machine.program_ptr - machine.machine_memory);
    *machine.program_ptr++ = opcodes_find("QUIT");
    BYTE i;
    for(i = 0; i < machine.lablel_number; i++)
        label_set_jumps(&machine.progam_labels[i]);

    for(i = 0; i < machine.var_number; i++)
    {
        printf("Var %d allocation [PTR] =%d\n", i+1, machine.program_ptr - machine.machine_memory);
        var_set_links(&machine.variables[i],(DWORD) (machine.program_ptr - machine.machine_memory), machine.machine_memory);
        *machine.program_ptr++ = 0;
    }

    fclose(fp);

    write_binary(ooutput_file, &machine);
}
