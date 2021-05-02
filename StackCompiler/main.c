#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"
#include "../common/opcodes.h"
#include "src/token.h"
#define MAX_LEN 256
#include "src/machine.h"

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


    while (fgets(line, MAX_LEN - 1, fp))
    {
        // Remove trailing newline
        //buffer[strcspn(buffer, "\n")] = 0;
        printf("%s\n", line);
        BYTE ntokens;
        tokens = str_split(&ntokens, line, ',');
        if (tokens)
        {
            int i;
            for (i = 0; *(tokens + i); i++)
            {
                char* token = *(tokens + i);

                str_to_upper(token);

                if(token_is_comment(token))
                {
                    printf("Comment found =[%s]\n", (char*) line);

                }
                else if(token_is_var(token))
                {
                   if(ntokens == 2)
                   {
                        char* argument = *(tokens + i + 1);
                        var_init(variable_ptr, token);
                        variable_ptr++;
                   }
                   if(ntokens == 3)
                   {
                        perror("FATAL: array not implemented yet");
                        break;
                   }
                   else
                   {
                        perror("FATAL: missing VAR arguments");
                        break;
                   }

                }

                else if(token_is_label(token))
                {
                    printf("label found=[%s]\n", (char*) token);
                    label_init(variable_ptr, token);
                    label_ptr++;
                    breakl;
                }


                if(token_unknown(token))
                {
                    perror("Unexpected command");
                }
                else if(token_is_control(token))
                {
                    printf("token=[%s]\n", (char*) token);
                    continue;
                }
                else if(token_is_mem(token))
                {
                    printf("token=[%s]\n", (char*) token);
                    continue;
                }

                else

                    perror("Unexpected command");



                free(token);
            }
            printf("\n");
            free(tokens);
        }
    }

    fclose(fp);
    return 0;
}
