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
            Machine interpreter;
            machine_initialize(&interpreter);
            printf("Ready\n>");
            while ((read = getline(&line, &len, stdin) != -1))
            {
                if(compile_line(line, &interpreter))

                {
                    printf("OK\n>");
                }
                else
                    printf("Error\n>");
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
