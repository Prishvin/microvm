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
BOOL compile_line(char* line, Machine* mac)
{
    BOOL result = TRUE;
#ifdef DEBUG_COMPILE
    printf("[Processing line]\n %s", line);
#endif
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
#ifdef DEBUG_COMPILE
                printf("Comment found =[%s]\n", (char*) line);
#endif
                free(tokens);
                return FALSE;

            }
            else if(token_is_var(token))
            {
                if(ntokens == 2)
                {
                    char* argument = *(tokens + i + 1);
                    var_init(mac->variable_ptr, argument);
                    mac->variable_ptr->index = mac->variable_ptr - mac->variables;
                    mac->variable_ptr->address = mac->variable_memory_ptr++;
                    mac->variable_ptr++;
                    mac->var_number++;


                    free(tokens);
                    return FALSE;
                }
                if(ntokens == 3)
                {
                    perror("FATAL: array not implemented yet");
                    free(tokens);
                    return FALSE;
                }
                else
                {
                    perror("FATAL: wrong VAR arguments");
                    free(tokens);
                    return FALSE;
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
                lb->address = mac->program_ptr;
#ifdef DEBUG_COMPILE
                printf("Label ptr =%d\n", mac->program_ptr - mac->machine_memory);
#endif
                //mac->program_ptr++;

                free(tokens);
                return FALSE;
            }
            else
            {
                DWORD op =  opcodes_find(token);
#ifdef DEBUG_COMPILE
                printf("%s [PTR]=%d\n", token, mac->program_ptr - mac->machine_memory);
#endif


                if(token_unknown(op))
                {
                    perror("FATAL: Unexpected opcode");
                    result =  FALSE;
                }
                *mac->program_ptr++ = op;//add opcode if opcode is not var and label


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
                        DWORD jump = mac->program_ptr - mac->machine_memory;
                        *(lb->jump_ptr++) = jump;
                        lb->jump_number++;
#ifdef DEBUG_COMPILE
                        printf("Label %s ptr =%d\n", argument,  mac->program_ptr - mac->machine_memory);
#endif
                        *mac->program_ptr++ = 0; // label address will be garbage at thi point. label adress to be set after progam is compiled
                        result = TRUE;
                    }
                    else
                    {
                        perror("FATAL: no argument supplied");
                        result =  FALSE;
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
#ifdef DEBUG_COMPILE
                            printf("Numberic argument %s\n [PTR] =%d\n", argument,  mac->program_ptr - mac->machine_memory);
#endif // DEBUG_COMPILE
                            *mac->program_ptr++=number;
                        }
                        else
                        {
                            variable* var = variable_find(argument, mac->variables,  mac->variable_ptr);
                            if((DWORD) var == VARIABLE_NOT_FOUND)
                            {
                                perror("FATAL: variable not found");
                                return FALSE;
                            }
                            else
                            {
#ifdef DEBUG_COMPILE
                                printf("Link argument %s ptr =%d\n", argument,  mac->program_ptr - mac->machine_memory);
#endif
                                *(var->link_ptr++) =mac->program_ptr - mac->machine_memory;

#ifdef HARVARD_A
                                *mac->program_ptr++ = var->index;
#else
                                *mac->program_ptr++ = 0;
#endif
                            }

                        }
                    }
                    else
                    {
                        perror("FATAL: no argument supplied");
                        result =  FALSE;
                    }
                }
                else if(token_is_print(token))
                {
                    char* argument = *(tokens + 1);
                    DWORD number;
                    if(is_numeric(argument, &number))
                    {

                        *mac->program_ptr++=number;
                    }
                    else
                    {
                        *mac->program_ptr++;
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


            }
            free(token);
        }
        printf("\n");
        free(tokens);
    }
    return result;
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
    machine_initialize(&machine);

    while (fgets(line, MAX_LEN - 1, fp))
    {
        compile_line(line, &machine);
    }
    printf("QUIT ptr =%d\n",  machine.program_ptr - machine.machine_memory);
    *machine.program_ptr++ = opcodes_find("QUIT");
    BYTE i;
    for(i = 0; i < machine.lablel_number; i++)
        label_set_jumps(&machine.progam_labels[i]);

#ifdef HARVARD
    printf("Harvard defined, skippind var allocation");
#else
    printf("Harvard not defined, allocating variables");
    for(i = 0; i < machine.var_number; i++)
    {
        printf("Var %d allocation [PTR] =%d\n", i+1, machine.program_ptr - machine.machine_memory);
        var_set_links(&machine.variables[i],(DWORD) (machine.program_ptr - machine.machine_memory), machine.machine_memory);
        *machine.program_ptr++ = 0;
    }
#endif

    fclose(fp);

    write_binary(ooutput_file, &machine);
}