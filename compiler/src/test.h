#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "../../common/global.h"
#include "../../common/auxillary.h"
#include "compiler.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "compiler.h"
#include "../../common/global.h"
BOOL run_test(char* dirname)
{
    DWORD len;
    BOOL result = RESULT_OK;
    struct dirent * dir;
    DIR  *d = opendir(dirname);
    char binary[256]= "binary.b";
    char path[256];
    BYTE n = 0;
    char* filename;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            n++;
            len = strlen(dir->d_name);
            filename =dir->d_name;
            if(filename[len-1] == 'p')
            {
                printf("[TEST] run> %s\n", filename);
                strcpy(path, dirname);
                strcat(path, filename);
                if(compile_to_binary(path, binary) == RESULT_OK)
                    result = run_binary(binary, FALSE);
                else
                {
                    errno =EPROTO ;
                    result = EPROTO;
                    perror("[FAIL] test fail");
                    break;
                }

                if(result)
                {
                    errno =EPROTO ;
                    result = EPROTO;
                    perror("[FAIL] test fail");
                    break;
                }
                else
                {
                        printf("[PASS] \n");
                }
            }
        }
        if(result == RESULT_OK)
        {
            printf("[TEST] %d all test passed \n", n);
            getchar();
        }
        else
        {
             printf("[TEST] fail at %s\n", filename);
        }
        closedir(d);
    }
    else
    {
        errno =ENOTDIR ;
        result = ENOTDIR;
        perror("[FAIL] cont open test directory");
    }

    return result;
}


#endif // TEST_H_INCLUDED
