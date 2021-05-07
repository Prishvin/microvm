#include <stdio.h>
#include <stdlib.h>
#include "src/global.h"
#include  "src/opcodes.h"
#include "src/machine.h"
#include "src/auxillary.h"

#define MAX_LEN 256

int main( int argc, char *argv[] )
{
   if( argc == 3 ) {
      printf("Processing file %s. Binery output to %s\n", argv[1],argv[2]);
   }
   else if( argc > 3 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
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
    while (fgets(line, MAX_LEN - 1, fp))
    {
        // Remove trailing newline
        //buffer[strcspn(buffer, "\n")] = 0;
        printf("%s\n", line);
        tokens = str_split(line, ',');
        if (tokens)
        {
            int i;
            for (i = 0; *(tokens + i); i++)
            {
                char* token = *(tokens + i);

                printf("month=[%s]\n", (char*) token);
                free(token);
            }
            printf("\n");
            free(tokens);
        }
    }

    fclose(fp);
    return 0;
}
