#include "auxillary.h"
#include <unistd.h>


void clrscr()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    printf("\n>");
}
void node_init(node* ptr, node* l, node* r, DWORD i, DWORD arg)
{
    ptr->nchilds = 0;
    ptr->left = l;
    ptr->right = r;
    ptr->index = i;
    ptr->argument = arg;

}




char** str_split(BYTE* ntokens, char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    char len = strlen(a_str);
    *(a_str + len - 1) = 0;
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            //assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        //  assert(idx == count - 1);
        *(result + idx) = 0;
    }
    *ntokens = count - 1;
    return result;
}

//
BOOL str_in_array(char (*arr)[MAX_OPCODE_STR_LENGTH], char* str)
{
    BYTE i;
    for(i = 0;**(arr + i); i++)
        if(strcmp(*(arr + i), str)==0)
            return TRUE;

    return FALSE;
}

void str_to_upper(char* temp)
{
 if(temp != 0)
    {

    char * name;
    name = strtok(temp,":");

    // Convert to upper case
    char *s = name;
     while (*s)
        {
            *s = toupper((unsigned char) *s);
            s++;
        }
    }

}

char str_is_number(char *text)
{
    int j;
    j = strlen(text);
    while(j--)
    {
        if(text[j] >= '0' && text[j] <= '9')
            continue;

        return 0;
    }
    return 1;
}

BOOL is_numeric(char* name, DWORD* number)
{


    if(name != 0 && str_is_number(name))
    {
        *number = strtoul(name, 0,10 );
        return TRUE;
    }
    else
    {
        return FALSE;
    }


}
void str_trim(char* str, char c)
{
    DWORD len = strlen(str);

    while(TRUE)
    {
        len = strlen(str);
        if(!(len > 0 && *(str + len - 1) ==c))
            break;
         *(str + len - 1) = 0;
    }

}
void str_shift_left(char myarray[], int sz, int shiftBy)
{
    if(shiftBy > sz)
    {
        shiftBy = shiftBy - sz;
    }

    if(sz == 1)
    {
        //do nothing
    }
    else

    {
        char temp;
        //for loop to print the array with indexes moved up (to the left) <-- by 2
        for (int i=0; i < sz-shiftBy; i++)
        {
            //EXAMPLE shift by 3  for a c-string of 5
            temp = myarray[i];//temp = myarray[0]
            myarray[i] = myarray[i + shiftBy];//myarray[0] == myarray[2]
            //myarray[i + shiftBy] = temp;//myarray[2] = temp(value previously at index i)
        }

    }
}
