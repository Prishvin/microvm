#include "compiler.h"
#include<stdio.h>
#include<stdlib.h>

int nconstants = 0;

void write_binary(char* filename, Machine* mac)
{
    DWORD i;
    FILE* fout=fopen(filename,"wb");
    if(fout !=NULL)
    {
        fwrite(mac->machine_memory, sizeof(DWORD), mac->program_ptr - mac->machine_memory + 1, fout );
    }
    fclose(fout);
}
void compile_file(char* input_file, char* output_file)
{

}

BOOL preprocessor_substitute(char* token)
{
    BOOL result = TRUE;
    DWORD i;
    int index;
    for(i = 0; i < nconstants; i++)
    {
        if(*token == CHAR_CONSTANT)
        {

            constant* c= constant_find(token, &index);
            if(index != -1)
            {

                strcpy(token, c->destination);
                break;
            }
            else
            {
                result = FALSE;
                break;
            }
        }
    }
    return result;
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
    DWORD number;
    if (tokens)
    {
        int i = 0;
        int n;
        for(i = 0; i<ntokens; i++)
        {
            if(!preprocessor_substitute(*(tokens+i)))
                return FALSE;
        }
        if(TRUE)
        {
            i = 0;
            char* token = *(tokens + i);
            str_to_upper(token);
            if(token_is_comment(token))
            {
#ifdef DEBUG_COMPILE
                printf("Comment found =[%s]\n", (char*) line);
#endif
                free(tokens);
                return TRUE;
            }
            else if(token_is_var(token))
            {
                if(ntokens == 2)
                {
                    char* argument = *(tokens + i + 1);
                    var_init(mac->variable_ptr, argument);
                    mac->variable_ptr->index = 0;
                    mac->variable_ptr->address =  mac->variable_ptr - mac->variables;
                    mac->variable_ptr++;
                    mac->var_number++;
                    free(tokens);
                    return TRUE;
                }
                if(ntokens == 3)
                {
                    char* argument = *(tokens + i + 1);
                    char* arrstr = *(tokens + i + 2);
                    if(is_numeric(arrstr, &number))
                    {
                        for(n=0; n<number; n++)
                        {
                            var_init(mac->variable_ptr, argument);

                            mac->variable_ptr->address =  mac->variable_ptr - mac->variables;
                            mac->variable_ptr->index = n;
                            mac->variable_ptr++;
                            mac->var_number++;
                        }
                    }
                    else
                    {
                        errno = EINVAL;
                        perror("FATAL: wrong ARRAY arguments");
                    }
                    free(tokens);
                    return TRUE;
                }
                else
                {
                    errno = EINVAL;
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
                    label_init(mac->label_ptr++, token,  mac->program_ptr - mac->machine_memory);
                    mac->lablel_number++;
                }
                label* lb = label_find(token, mac->progam_labels, mac->label_ptr);
                lb->address = mac->program_ptr - mac->machine_memory;
#ifdef DEBUG_COMPILE
                printf("Label ptr =%d\n", mac->program_ptr - mac->machine_memory);
#endif
                //mac->program_ptr++;
                free(tokens);
                return TRUE;
            }
            else
            {
                DWORD op =  opcodes_find(token);
#ifdef DEBUG_COMPILE
                printf("%s [PTR]=%d\n", token, mac->program_ptr - mac->machine_memory);
#endif
                if(token_unknown(op))
                {
                    errno = EINVAL;
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
                        errno = EINVAL;
                        perror("FATAL: no argument supplied");
                        result =  FALSE;
                    }
                }
                else if(token_is_push(token))
                {
                    if(ntokens == 2)
                    {
                        char* argument = *(tokens + i + 1);

                        if(is_numeric(argument, &number))
                        {
#ifdef DEBUG_COMPILE
                            printf("Numberic argument %s\n [PTR] =%d\n", argument,  mac->program_ptr - mac->machine_memory);
#endif // DEBUG_COMPILE
                            *mac->program_ptr++=number;
                        }
                        else
                        {
                                errno = EINVAL;
                                 perror("FATAL: push expects numeric argument");
                                result =  FALSE;
                        }
                    }
                    else
                    {
                        errno = EINVAL;
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
                            *mac->program_ptr++= number;
                        }
                        else
                        {
                            variable* var = variable_find(argument, mac->variables,  0,  mac->variable_ptr);
                            if((DWORD) var == VARIABLE_NOT_FOUND)
                            {
                                errno = EINVAL;
                                perror("FATAL: variable not found");
                                return FALSE;
                            }
                            else
                            {
#ifdef DEBUG_COMPILE
                                printf("Link argument %s ptr =%d\n", argument,  mac->program_ptr - mac->machine_memory);
#endif
                                *(var->link_ptr++) =mac->program_ptr - mac->machine_memory;
                                *mac->program_ptr++ = var->address;
                            }
                        }
                    }
                    else
                    {
                        errno = EINVAL;
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
                        *mac->program_ptr++ = 1;
                    }
                }

                else if(token_is_dup(token))
                {
                    if(ntokens == 1)
                    {
                        printf("Dup ptr =%d\n",  mac->program_ptr - mac->machine_memory);
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
BOOL preprocessor(char* line, Machine* mac)
{
    BOOL result = TRUE;
    str_shift_left(line, strlen(line), 1);
    char** tokens;
    BYTE ntokens;
    tokens = str_split(&ntokens, line, ' ');

    if(ntokens>2 && strcmp(tokens[0], PRE_DEFINE) == 0)
    {
        int index;
        constant* c = constant_find(*(tokens+1), &index);
        if(index == -1)
        {
            c = &constants[nconstants++];
        }
        str_trim(*(tokens+2), '\n');
        strcpy(c->source, *(tokens+1));
        strcpy(c->destination, *(tokens+2));

    }
    free(tokens);

    return result;
}

constant* constant_find(char* name, int* index)
{
    DWORD i;
    *index = -1;
    for(i = 0; i < nconstants; i++)
    {
        if(strcmp(name, constants[i].source)==0)
        {
            *index = i;
            return &constants[i];
        }
    }

    return NULL;
}
BOOL compile_all(char* input_file, char* ooutput_file)
{
    BOOL result = TRUE;

    FILE* fp;
    fp = fopen(input_file, "r");
    if (fp == NULL)
    {
        errno = EBADF;
        perror("Failed: ");
        return 1;
    }
    char line[MAX_LEN];
    // -1 to allow room for NULL terminator for really long string
    machine_initialize(&machine);
    DWORD line_number = 1;
    while (fgets(line, MAX_LEN - 1, fp))
    {
        if(*line == '$') //preprocessor
        {

            if(strlen(line)>1)
                preprocessor(line, &machine);
        }
        else
        {
        if(strlen(line)>1)
        {
            if(!compile_line(line, &machine))
            {
                printf("[ERROR] at [line %d] > %s\n",line_number, line );
                return FALSE;
                break;
            }
             line_number++;
            }
        }

    }
    printf("QUIT ptr =%d\n",  machine.program_ptr - machine.machine_memory);
    *machine.program_ptr++ = opcodes_find("QUIT");
    BYTE i;
    for(i = 0; i < machine.lablel_number; i++)
        label_set_jumps(&machine.progam_labels[i]);

#ifdef HARVARD
    printf("Variable allocated\n");
#else
    printf("Harvard not defined, allocating variables\n");
    for(i = 0; i < machine.var_number; i++)
    {
        printf("Var %d allocation [PTR] =%d\n", i+1, machine.program_ptr - machine.machine_memory);
        var_set_links(&machine.variables[i],(DWORD) (machine.program_ptr - machine.machine_memory), machine.machine_memory);
        *machine.program_ptr++ = 0;
    }
#endif

    fclose(fp);

    write_binary(ooutput_file, &machine);
    return result;
}
