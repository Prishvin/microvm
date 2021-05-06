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

    if(argc == 2)
    {
        if(strcmp(argv[1],"-h") == 0)
        {
            printf("Compile file: stackcompiler -c source_file destination_file\n");
            printf("Run interpreter:  stackcompiler -i\n");
        }
        if(strcmp(argv[1],"-i") == 0)
        {
            while ((read = getline(&line, &len, stdin) != -1))
            {
                printf("%s", line);
            }
        }


    }
    if(argc == 3)
    {
        compile_all(argv[2], argv[3]);
    }
}
