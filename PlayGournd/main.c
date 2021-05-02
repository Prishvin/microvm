#include <stdio.h>
#include <stdlib.h>
#include "../common/global.h"
#include "../common/auxillary.h"

char token_control[9][10]= {"CALL", "JGE", "JLE", "JG", "JL", "JNE", "JE", "JMP",""};
char token_memory[6][10] =  {"PUSH", "FROMMEM", "TOMEM", "AFROM", "ATOM", ""};

BOOL string_in_array(char (*arr)[10], char* str)
{
  BYTE i;
  for(i = 0;**(arr + i);i++)
    if(strcmp(*(arr + i), str)==0)
        return TRUE;

  return FALSE;
}

int main()
{
    printf("Hello world!\n");

    char line[] = "Programming is fun CALL JGE";
    char** tokens = str_split(line, ' ');
        if (tokens)
        {
            int i;
            for (i = 0; *(tokens + i); i++)
            {
                char* token = *(tokens + i);
                string_in_array(token_control, token);
                printf("month=[%s]\n", (char*) token);
                free(token);
            }
            printf("\n");
            free(tokens);
        }
    return 0;
}
