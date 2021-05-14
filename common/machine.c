#include "machine.h"


Machine machine;
void machine_load(char* filename, Machine* mac)
{

    FILE *fileptr;
    char *buffer;
    long filelen;

    fileptr = fopen(filename, "rb");  // Open the file in binary mode
    if(fileptr == NULL)
    {
        errno = ENOENT;
        perror("FATAL: reading binary file");
        return;
    }
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file

    memcpy(&mac->machine_memory, buffer, filelen);
    free(buffer);

}
void machine_initialize(Machine *mac)
{
    mac->program_ptr = mac->machine_memory; //now pointer is at first instruction
    mac->variable_ptr = mac->variables;
    mac->label_ptr = mac->progam_labels;
    mac->program_ptr = mac->machine_memory;

    mac->stack_first = mac->machine_stack;
    mac->stack_end = mac->machine_stack + STACK_SIZE;
    mac->stack_ptr = mac->stack_first;

    mac->memory_end = mac->machine_memory + DEVICE_MEMORY_SIZE;

    mac->call_ptr  = mac->machine_call_stack;
    mac->call_stack_end = mac->machine_call_stack + STACK_SIZE;

    mac->call_first = mac->machine_stack;
    mac->var_number = 0;
    mac->progam_cursor_mask = 0xFFF;

    mac->section_var = mac->program_ptr;
    mac->section_str = mac->program_ptr;

    mac->variable_memory_ptr =mac->variable_memory;
}

void read_inputs();
void update_outputs();


void halt()
{
    if(machine.mode != MACHINE_MODE_INTERPRETER)
    {
        errno = EFAULT;
        perror("Execution halted");
        getchar();
        exit(-1);
    }
}

void increment_program_ptr()
{
    machine.program_ptr++;
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.program_ptr>=machine.memory_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
}

void increment_stack_cursor() //+
{
    machine.stack_ptr++;
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr>=machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
}
void decrement_stack_cursor() //+
{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr==machine.machine_stack)
        halt();
#endif
    machine.stack_ptr--;
}

void push()
{
    increment_program_ptr(); //push is followed by one byte, so increment to skip argument
    *machine.stack_ptr = *machine.program_ptr;
    increment_stack_cursor();
#ifdef TRACE_VM
    printf("{PUSH}\n");
    bp();
#endif
}
void pop()
{
    decrement_stack_cursor();
#ifdef TRACE_VM
    printf("{POP}\n");
    bp();
#endif
}

void add() //+
{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) + *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{ADD}\n");
    bp();
#endif
}
void sub() //+

{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) - *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{SUB}\n");
    bp();
#endif
}
void mult() //+
{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) * (*machine.stack_ptr);
#ifdef TRACE_VM
    printf("{MULT}\n");
    bp();
#endif
}
void divide()
{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    if(!*machine.stack_ptr)
        halt();
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) / *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{DIV}\n");
    bp();
#endif
}
void jmp() //+
{
    increment_program_ptr(); //increment because argument byte
    machine.program_ptr = machine.machine_memory +  *machine.program_ptr;
    machine.program_ptr--;
#ifdef TRACE_VM
    printf("{JMP}\n");
    bp();
#endif
}

void cmp() // lower is grater
{
    machine.stack_ptr--;
    if(machine.stack_ptr> machine.stack_first && machine.stack_ptr < machine.stack_end)
    {
        if (*(machine.stack_ptr-1) == *machine.stack_ptr)
        {
            machine.flag_eq = 1;
            machine.flag_gr = 0;
        }
        else
        {
            machine.flag_eq = 0;
            if (*(machine.stack_ptr-1) > *machine.stack_ptr)
                machine.flag_gr = 1;
            else
                machine.flag_gr = 0;
        }
    }
    else
        halt();
    machine.stack_ptr++;
#ifdef TRACE_VM
    printf("{CMP}\n");
    bp();
#endif
}


void je() /// jump if equal, 8byte (skip one byte)
{
    if (machine.flag_eq == 1)
    {
        machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1);
        machine.program_ptr--;  //
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after je");
#endif // MEMORY_CHECKS_ENABLED
    }
     else
    {
        machine.program_ptr++; //skip argument
    }
#ifdef TRACE_VM
    printf("{JE}\n");
    bp();
#endif
}


void jne() /// jump if not equal flag is set. 8 byte(skip one byte)
{
    if (machine.flag_eq == 0)
    {
        machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1);
        machine.program_ptr--;  //
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jne");
#endif // MEMORY_CHECKS_ENABLED
    }
     else
    {
        machine.program_ptr++; //skip argument
    }
#ifdef TRACE_VM
    printf("{JNE}\n");
    bp();
#endif
}

void jl()
{
    if (machine.flag_eq == 0 && machine.flag_gr == 0)
    {
        machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1);
        machine.program_ptr--;  //
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jl");
#endif // MEMORY_CHECKS_ENABLED
    }
     else
    {
        machine.program_ptr++; //skip argument
    }
#ifdef TRACE_VM
    printf("{JL}\n");
    bp();
#endif
}
void jg()
{
    if (machine.flag_gr)
    {
        machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1);
        machine.program_ptr--;  //

#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jg");
#endif // MEMORY_CHECKS_ENABLED
    }
     else
    {
        machine.program_ptr++; //skip argument
    }
#ifdef TRACE_VM
    printf("{JG}\n");
    bp();
#endif
}

void jle()
{
    if (!machine.flag_gr)
    {

        machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1);
        machine.program_ptr--;  //set to previos, since ptr will be incremented

#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jle");
#endif // MEMORY_CHECKS_ENABLED
    }
    else
    {
        machine.program_ptr++; //skip argument
    }
#ifdef TRACE_VM
    printf("{JLE}\n");
    bp();
#endif
}

void jge()
{
    if (machine.flag_eq || machine.flag_gr)
    {
        machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1);
        machine.program_ptr--;  //
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jle");
#endif // MEMORY_CHECKS_ENABLED
    }
     else
    {
        machine.program_ptr++; //skip argument
    }
#ifdef TRACE_VM
    printf("{JGE}\n");
    bp();
#endif
}

void frmm() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after frommem");
#endif // MEMORY_CHECKS_ENABLED
    *machine.stack_ptr = *(machine.variable_memory + *machine.program_ptr);
    increment_stack_cursor();
#ifdef TRACE_VM
    printf("{FRMM}\n");
    bp();
#endif
}

void tomm() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(machine.variable_memory + *machine.program_ptr) = *(machine.stack_ptr-1);
#ifdef TRACE_VM
    printf("{TOMM}\n");
    bp();
#endif
}

void sfrommem() //8
{
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after frommem");
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *machine.stack_ptr = *(machine.variable_memory + *(machine.stack_ptr) - 1);
#ifdef TRACE_VM
    printf("{SFRMM}\n");
    bp();
#endif
}

void stomem() //8
{
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(machine.variable_memory + *(machine.stack_ptr-2)) = *(machine.stack_ptr-1);
#ifdef TRACE_VM
    printf("{TOMM}\n");
    bp();
#endif
}

void afrom() //8
{
    increment_program_ptr();
    *(machine.stack_ptr -1 ) = *(machine.variable_memory + *(machine.stack_ptr -1 ) + *machine.program_ptr);
#ifdef TRACE_VM
    printf("{AFROM}\n");
    bp();
#endif
}

void atom() //8
{
    increment_program_ptr();
    *(machine.variable_memory + *(machine.stack_ptr - 1 ) + *machine.program_ptr) = *(machine.stack_ptr- 2);
#ifdef TRACE_VM
    printf("{ATOM}\n");
    bp();
#endif
}


void call()
{
    DWORD tmp =  machine.program_ptr - machine.machine_memory;; //save ptr
    machine.program_ptr =machine.machine_memory + *(machine.program_ptr + 1); //now
    machine.program_ptr--;  //set to previos, since ptr will be incremented
    *machine.call_ptr = tmp+1;
    machine.call_ptr++;
    //TODO add checks
#ifdef TRACE_VM
    printf("{CALL}\n");
    bp();
#endif
}

void ret()
{
    machine.program_ptr = machine.machine_memory +*(--machine.call_ptr);
#ifdef TRACE_VM
    printf("{RET}\n");
    bp();
#endif
}

void duplicate()
{
    *machine.stack_ptr = *(machine.stack_ptr - 1);
    *machine.stack_ptr++;
#ifdef TRACE_VM
    printf("{DUP}\n");
    bp();
#endif
}

void randint()
{

}

void swap()
{
    DWORD temp = *(machine.stack_ptr-1);
    *(machine.stack_ptr-1) = *(machine.stack_ptr-2);
    *(machine.stack_ptr-2) = temp;
#ifdef TRACE_VM
    printf("{SWAP}\n");
    bp();
#endif
}




void inc()
{
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1)  + 1;
#ifdef TRACE_VM
    printf("{INC}\n");
    bp();
#endif
}

void dec()
{
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1)  - 1;
#ifdef TRACE_VM
    printf("{DEC}\n");
    bp();
#endif
}

void stinc()
{
    if (machine.stack_ptr < machine.stack_first)
        halt("cannot dec because stack is empty");
    machine.stack_ptr = machine.stack_ptr  + 1;
#ifdef TRACE_VM
    printf("{INC}\n");
    bp();
#endif
}
void stdec()
{
    if (machine.stack_ptr < machine.stack_first)
        halt("cannot dec because stack is empty");
    machine.stack_ptr = machine.stack_ptr  - 1;
#ifdef TRACE_VM
    printf("{DEC}\n");
    bp();
#endif
}

void nop()
{
#ifdef TRACE_VM
    printf("{NOP}\n");
    bp();
#endif
    ;
}
void succ_exit()
{
#ifdef TRACE_VM
    printf("{EXIT}\n");
    bp();
#endif
    ;
}
void  quit()
{
    DWORD value = *(machine.stack_ptr-1);
    if(value)
    {
        errno = value;
        perror("Abnormal termination");
    }
    else
    {
        errno = 0;
        printf("[SUCCESS]");
    }
    getchar();
    exit(value);
    succ_exit();
}
void aprint()
{
    DWORD* ptr = machine.machine_stack;
    increment_program_ptr();
    DWORD n = *machine.program_ptr;
    DWORD i=0;
    printf("Top %d stack values:\n", n);
    while(i++<n)
    {
        printf(" 0x%02X", *(machine.stack_ptr -n + i - 1) );
    }
    printf("\n>");
}
void adelay()
{
    increment_program_ptr();
    usleep(*machine.program_ptr*1000000);
#ifdef TRACE_VM
    printf("{DELAY}\n");
    bp();
#endif
}
void astate()
{
    printf("Breakpoint reached at 0x%x\n", machine.program_ptr-machine.machine_memory);
    printf("Call stack depth: %i\n", machine.call_ptr-machine.call_first);
    printf("Stack depth: %i\n", machine.stack_ptr-machine.machine_stack);
    printf("Flags EQ: %d, GR %d\n", machine.flag_eq,machine.flag_gr);
    printf("Stack content:\n");
    printf("Program ptr = [%d]\n", machine.program_ptr - machine.machine_memory);
    printf("Stack   ptr = [%d]\n", machine.stack_ptr - machine.machine_stack);
    int i;
    DWORD* ptr = machine.stack_first;
    while(ptr<machine.stack_ptr)
    {
        printf("0x%02X ", *ptr);
        if(i%4 == 0)
            printf("\n");
        ptr++;
        i++;
    }
    printf("\n");
}
void bp()
{
    astate();
    getchar();
}

void land()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) && *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{LAND}\n");
    bp();
#endif
}
void lor()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) || *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{LOR}\n");
    bp();
#endif
}
void lxor()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = (*(machine.stack_ptr-1) ^ *machine.stack_ptr)>0;
#ifdef TRACE_VM
    printf("{LXOR}\n");
    bp();
#endif
}
void lnot()
{
    machine.stack_ptr;
    *(machine.stack_ptr-1) = !(*(machine.stack_ptr-1));
#ifdef TRACE_VM
    printf("{LNOR}\n");
    bp();
#endif
}

void band()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) & *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{BAND}\n");
    bp();
#endif
}
void bor()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) | *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{BOR}\n");
    bp();
#endif
}
void bxor()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) ^ *machine.stack_ptr;
#ifdef TRACE_VM
    printf("{BXOR}\n");
    bp();
#endif
}
void bnot()
{
    *(machine.stack_ptr-1) = ~(*(machine.stack_ptr-1));
#ifdef TRACE_VM
    printf("{BNOT}\n");
    bp();
#endif
}

void asrt()
{
    cmp();
    if(!machine.flag_eq)
    {
        errno = EINPROGRESS;
        perror("[FAIL] assertation");
        halt();
    }
}
void ptrto()
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after frommem");
#endif // MEMORY_CHECKS_ENABLED

    *(machine.stack_ptr) =  *((DWORD*)*(machine.program_ptr));
    machine.stack_ptr++;

#ifdef TRACE_VM
    printf("{FRMM}\n");
    bp();
#endif
}
void toptr()
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *((DWORD*)*(machine.program_ptr)) = *(machine.stack_ptr-1);

#ifdef TRACE_VM
    printf("{TOMM}\n");
    bp();
#endif
}


