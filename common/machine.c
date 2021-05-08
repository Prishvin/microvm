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

    mac->stack_first = mac->machine_stack+1;
    mac->stack_end = mac->machine_stack + STACK_SIZE;
    mac->stack_ptr = mac->stack_first;

    mac->memory_end = mac->machine_memory + DEVICE_MEMORY_SIZE;


    mac->call_first = mac->machine_stack;
    mac->var_number = 0;
    mac->progam_cursor_mask = 0xFFF;

    mac->section_var = mac->program_ptr;
    mac->section_str = mac->program_ptr;

    mac->variable_memory_ptr =mac->variable_memory;
}

void read_inputs();
void update_outputs();


void halt() {}

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
    if(machine.stack_ptr==machine.machine_stack)
        halt();
    machine.stack_ptr--;
#ifdef MEMORY_CHECKS_ENABLED

#endif
}

void push()
{
    increment_program_ptr(); //push is followed by one byte, so increment to skip argument
    *machine.stack_ptr = *machine.program_ptr;
    increment_stack_cursor();
    increment_program_ptr(); //increment program_ptr to skip argument
}
void pop()
{
    decrement_stack_cursor();
}

void add() //+
{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) + *machine.stack_ptr;

}
void sub() //+

{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) - *machine.stack_ptr;
}
void mult() //+
{

#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) * (*machine.stack_ptr);

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
}
void jmp() //+
{
    increment_program_ptr(); //increment because argument byte
    machine.program_ptr = *machine.program_ptr;
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
}


void je() /// jump if equal, 8byte (skip one byte)
{

    if (machine.flag_eq == 1)
    {
        machine.program_ptr = *machine.program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after je");
#endif // MEMORY_CHECKS_ENABLED
    }
}


void jne() /// jump if not equal flag is set. 8 byte(skip one byte)
{
    if (machine.flag_eq == 0)
    {
        machine.program_ptr = *machine.program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jne");
#endif // MEMORY_CHECKS_ENABLED
    }
}

void jl()
{


    if (machine.flag_eq == 0 && machine.flag_gr == 0)
    {
        machine.program_ptr = *machine.program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jl");
#endif // MEMORY_CHECKS_ENABLED
    }
}
void jg()
{

    if (machine.flag_gr)
    {
        machine.program_ptr = *machine.program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jg");
#endif // MEMORY_CHECKS_ENABLED
    }
}

void jle()
{

    if (!machine.flag_gr)
    {
        machine.program_ptr = *machine.program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jle");
#endif // MEMORY_CHECKS_ENABLED
    }
}

void jge()
{

    if (machine.flag_eq && machine.flag_gr)
    {
        machine.program_ptr = *machine.program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
        if (machine.program_ptr >= machine.memory_end)
            halt("Segmentation fault after jle");
#endif // MEMORY_CHECKS_ENABLED
    }

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
    increment_program_ptr();
}

void tomm() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(machine.variable_memory + *machine.program_ptr) = *(machine.stack_ptr-1);
    increment_program_ptr();
}

void sfrommem() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after frommem");
#endif // MEMORY_CHECKS_ENABLED

    increment_stack_cursor();
    *machine.stack_ptr = *(machine.program_ptr + *machine.program_ptr - 1);
}

void stomem() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(machine.program_ptr + *machine.stack_ptr - 1) = *machine.stack_ptr;
}

void afrom() //8
{
    //TODO aserts here
    increment_program_ptr();
    increment_stack_cursor();
    *machine.stack_ptr = *(machine.machine_memory + *(machine.stack_ptr -1 ) + *machine.program_ptr);
}

void atom() //8
{
    //TODO aserts here
    increment_program_ptr();
    *(machine.machine_memory + *(machine.stack_ptr -1 ) + *machine.program_ptr) = *machine.stack_ptr;
}


void call()
{
    machine.call_ptr++;
    if (machine.call_ptr >= machine.call_stack_end)
        halt("call stack overflow");
    *machine.call_ptr = machine.program_ptr+2;
    increment_program_ptr();
    if (machine.program_ptr >= machine.memory_end)
        halt("segmentation fault in call");
    machine.program_ptr = *machine.program_ptr;
}

void ret()
{
    if (machine.call_ptr < machine.call_first)
        halt("cannot ret: call stack is empty");
    if (machine.call_ptr < machine.call_first || machine.call_ptr >= machine.call_stack_end)
        halt("segmentation fault in ret");
    *machine.program_ptr = *machine.call_ptr--;

}

void adup()
{

   *machine.stack_ptr = *(machine.stack_ptr - 1);
    *machine.stack_ptr++;
}

void randint()
{

}

void swap()
{
    if (machine.stack_ptr < machine.stack_second)
        halt("not enough elements in stack to swap");
    DWORD temp = *machine.stack_ptr;
    *machine.stack_ptr = *(machine.stack_ptr-1);
    *(machine.stack_ptr-1) = temp;
}

void stinc()
{
    if (machine.stack_ptr >= machine.stack_end)
        halt("cannot inc because stack is empty");
    machine.stack_ptr++;
}

void stdec()
{
    if (machine.stack_ptr < machine.stack_first)
        halt("cannot dec because stack is empty");
    machine.stack_ptr--;
}
void inc()
{
    if (machine.stack_ptr < machine.stack_first)
        halt("cannot dec because stack is empty");
    *machine.stack_ptr = *machine.stack_ptr + 1;
}
void dec()
{
    if (machine.stack_ptr < machine.stack_first)
        halt("cannot dec because stack is empty");
    *machine.stack_ptr = *machine.stack_ptr - 1;
}

void sttoar()
{
    /*
        if (machine.stack_ptr < machine.stack_first)
            halt("stack is empty, cannot afrommem");
        increment_program_ptr();
        if (stack[st_cur] + mem[c_cur] < 0 || stack[st_cur] + mem[c_cur] >= MEM_SIZE)
            halt("segmentation fault in afrommem");
        inc_st_cur();
        stack[st_cur] = mem[stack[st_cur - 1] + mem[c_cur]];*/
}

void artost()
{
//    if (st_cur < 1)
    //      halt("Not enough elements in stack for atomem");
    increment_program_ptr();
    //if (stack[st_cur - 1] + mem[c_cur] < 0 || stack[st_cur - 1] + mem[c_cur] >= MEM_SIZE)
    //    halt("segmentation fault in atomem");
    *(machine.machine_memory + *machine.program_ptr + *machine.stack_ptr - 1) = *machine.stack_ptr;
}

void nop()
{
    ;
}
void succ_exit()
{
    ;
}
void  quit()
{
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
}
void astate()
{
    printf("Breakpoint reached at 0x%x\n", machine.program_ptr-machine.machine_memory);
    printf("Call stack depth: %i\n", machine.call_ptr-machine.call_first);
    printf("Stack depth: %i\n", machine.stack_ptr-machine.machine_stack);
    printf("Stack content:\n");
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
}
void lor(){
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) || *machine.stack_ptr;
}
void lxor(){
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = (*(machine.stack_ptr-1) ^ *machine.stack_ptr)>0;
}
void lnot()
{
    machine.stack_ptr;
    *(machine.stack_ptr-1) = !(*(machine.stack_ptr-1));
}

void band()
{
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) & *machine.stack_ptr;
}
void bor(){
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) | *machine.stack_ptr;
}
void bxor(){
    machine.stack_ptr--;
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) ^ *machine.stack_ptr;
}
void bnot(){

    *(machine.stack_ptr-1) = ~(*(machine.stack_ptr-1));
}
