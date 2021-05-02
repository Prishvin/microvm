#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include "../../common/global.h"
#include "../../common/variable.h"
#include "../../common/label.h"


#define DEVICE_MEMORY_SIZE  4096
#define VARIABLE_MEMORY_SIZE 512
#define LABEL_MEMORY_SIZE 512
#define STACK_SIZE 2048



#define MEMORY_CHECKS_ENABLED // disable this to save processing time. might result in aegmentation fault.

DWORD progam_labels[LABEL_MEMORY_SIZE];
variable progam_variables[VARIABLE_MEMORY_SIZE];
label progam_labels[MAX_LABELS];
label* label_ptr;

DWORD machine_memory[DEVICE_MEMORY_SIZE];
DWORD* memory_end;
DWORD* stack_end;
DWORD* stack_first;
DWORD* stack_second;
DWORD* call_stack_end;
DWORD* call_first;
DWORD machine_call_stack[STACK_SIZE];
DWORD machine_stack[STACK_SIZE]; //first value will always be 0 and treated as empty stack

DWORD progam_cursor_mask = 0xFFF;
DWORD* program_ptr;
variable* variable_ptr;

DWORD* stack_ptr;
DWORD* call_ptr;


BOOL flag_eq;
BOOL flag_gr;

long long ticks;

void machine_initialize()
{
    memory_end = machine_memory + DEVICE_MEMORY_SIZE;
    stack_end = machine_stack + STACK_SIZE;
    stack_first = machine_stack+1;
    call_first = machine_stack+1;
}

void read_inputs();
void update_outputs();


void halt() {}

static inline void increment_program_ptr()
{
    program_ptr++;
#ifdef MEMORY_CHECKS_ENABLED
    if(program_ptr>=memory_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
}

static inline void increment_stack_cursor() //+
{
    stack_ptr++;
#ifdef MEMORY_CHECKS_ENABLED
    if(stack_ptr>=stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
}
static inline void decrement_stack_cursor() //+
{
    if(stack_ptr==machine_stack)
        halt();
    stack_ptr--;
#ifdef MEMORY_CHECKS_ENABLED

#endif
}

static inline void push() //+
{
    increment_program_ptr(); //push is followed by one byte, so increment to skip argument
    increment_stack_cursor();
    *machine_stack = *machine_memory;
}
static inline void pop()
{
    decrement_stack_cursor();
}

static inline void add() //+
{
#ifdef MEMORY_CHECKS_ENABLED
    if(stack_ptr < stack_second || stack_ptr >= stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    *(stack_ptr-1) = *(stack_ptr-1) + *stack_ptr;
}
static inline void sub() //+

{
#ifdef MEMORY_CHECKS_ENABLED
    if(stack_ptr < stack_second || stack_ptr >= stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    *(stack_ptr-1) = *(stack_ptr-1) - *stack_ptr;
}
static inline void mult() //+
{

#ifdef MEMORY_CHECKS_ENABLED
    if(stack_ptr < stack_second || stack_ptr >= stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    *(stack_ptr-1) = *(stack_ptr-1) * (*stack_ptr);

}
static inline void divide()

{
#ifdef MEMORY_CHECKS_ENABLED
    if(stack_ptr < stack_second || stack_ptr >= stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    if(!*stack_ptr)
    halt();
    *(stack_ptr-1) = *(stack_ptr-1) / *stack_ptr;
}
static inline void jmp() //+
{
    increment_program_ptr(); //increment because argument byte
    program_ptr = *program_ptr;
}

static inline void cmp() // lower is grater
{
    if(stack_ptr> stack_first && stack_ptr < stack_end)
    {
        if (*(stack_ptr-1) == *stack_ptr)
        {
            flag_eq = 1;
            flag_gr = 0;
        }
        else
        {
            flag_eq = 0;
            if (*(stack_ptr-1) > *stack_ptr)
                flag_gr = 1;
            else
                flag_gr = 0;
        }
    }
    else
        halt();
}


static inline void je() /// jump if equal, 8byte (skip one byte)
{

    if (flag_eq == 1)
    {
        program_ptr = *program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
                      if (program_ptr >= memory_end)
                          halt("Segmentation fault after je");
#endif // MEMORY_CHECKS_ENABLED
    }
}


static inline void jne() /// jump if not equal flag is set. 8 byte(skip one byte)
{
    if (flag_eq == 0)
    {
        program_ptr = *program_ptr;
        increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
                      if (program_ptr >= memory_end)
                          halt("Segmentation fault after jne");
#endif // MEMORY_CHECKS_ENABLED
    }
}

static inline void jl()
{


    if (flag_eq == 0 && flag_gr == 0)
    {
        program_ptr = *program_ptr;
          increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
                      if (program_ptr >= memory_end)
                          halt("Segmentation fault after jl");
#endif // MEMORY_CHECKS_ENABLED
    }
}
static inline void jg()
{

    if (flag_gr)
    {
        program_ptr = *program_ptr;
           increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
                      if (program_ptr >= memory_end)
                          halt("Segmentation fault after jg");
#endif // MEMORY_CHECKS_ENABLED
    }
}

static inline void jle()
{

    if (!flag_gr)
    {
        program_ptr = *program_ptr;
         increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
                      if (program_ptr >= memory_end)
                          halt("Segmentation fault after jle");
#endif // MEMORY_CHECKS_ENABLED
    }
}

static inline void jge()
{

    if (flag_eq && flag_gr)
    {
        program_ptr = *program_ptr;
           increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
                      if (program_ptr >= memory_end)
                          halt("Segmentation fault after jle");
#endif // MEMORY_CHECKS_ENABLED
    }

}

static inline void frommem() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (program_ptr >= memory_end)
        halt("Segmentation fault after frommem");
#endif // MEMORY_CHECKS_ENABLED

    increment_stack_cursor();
    *stack_ptr = *(program_ptr + *program_ptr);
}

static inline void tomem() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (program_ptr >= memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(machine_memory + *program_ptr) = *stack_ptr;
}

static inline void sfrommem() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (program_ptr >= memory_end)
        halt("Segmentation fault after frommem");
#endif // MEMORY_CHECKS_ENABLED

    increment_stack_cursor();
    *stack_ptr = *(program_ptr + *program_ptr - 1);
}

static inline void stomem() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (program_ptr >= memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(program_ptr + *stack_ptr - 1) = *stack_ptr;
}

static inline void afrom() //8
{
    //TODO aserts here
    increment_program_ptr();
    increment_stack_cursor();
    *stack_ptr = *(machine_memory + *(stack_ptr -1 ) + *program_ptr);
}

static inline void atom() //8
{
  //TODO aserts here
   increment_program_ptr();
   *(machine_memory + *(stack_ptr -1 ) + *program_ptr) = *stack_ptr;
}


static inline void call()
{
    call_ptr++;
    if (call_ptr >= call_stack_end)
        halt("call stack overflow");
    *call_ptr = program_ptr+2;
    increment_program_ptr();
    if (program_ptr >= memory_end)
        halt("segmentation fault in call");
    program_ptr = *program_ptr;
}

static inline void ret()
{
    if (call_ptr < call_first)
        halt("cannot ret: call stack is empty");
    if (call_ptr < call_first || call_ptr >= call_stack_end)
        halt("segmentation fault in ret");
    *program_ptr = *call_ptr--;

}

static inline void dup()
{
/*
    increment_program_ptr();
    int num = mem[c_cur];
    if (num < 1)
        halt("bad command dup argument");
    if (st_cur < num - 1)
        halt("cannot dup: not enough values in stack");
    int i;
    for(i = 0; i < num; i++)
    {
        inc_st_cur();
        stack[st_cur]  = stack[st_cur - num];
    }*/
}

static inline void randint()
{
    inc_st_cur();
//    stack[st_cur] = (rand() << 16) + rand() + rand() + rand() % 2;
}

static inline void swap()
{
    if (stack_ptr < stack_second)
        halt("not enough elements in stack to swap");
    DWORD temp = *stack_ptr;
    *stack_ptr = *(stack_ptr-1);
    *(stack_ptr-1) = temp;
}

static inline void stinc()
{
    if (stack_ptr >= stack_end)
        halt("cannot inc because stack is empty");
    stack_ptr++;
}

static inline void stdec()
{
    if (stack_ptr < stack_first)
        halt("cannot dec because stack is empty");
    stack_ptr--;
}

static inline void sttoar()
{
/*
    if (stack_ptr < stack_first)
        halt("stack is empty, cannot afrommem");
    increment_program_ptr();
    if (stack[st_cur] + mem[c_cur] < 0 || stack[st_cur] + mem[c_cur] >= MEM_SIZE)
        halt("segmentation fault in afrommem");
    inc_st_cur();
    stack[st_cur] = mem[stack[st_cur - 1] + mem[c_cur]];*/
}

static inline void artost()
{
//    if (st_cur < 1)
  //      halt("Not enough elements in stack for atomem");
    increment_program_ptr();
    //if (stack[st_cur - 1] + mem[c_cur] < 0 || stack[st_cur - 1] + mem[c_cur] >= MEM_SIZE)
    //    halt("segmentation fault in atomem");
    *(machine_memory + *program_ptr + *stack_ptr - 1) = *stack_ptr;
}

static inline void nop()
{
    ;
}
static inline void succ_exit() {;}
static inline void  quit()
{
    succ_exit();
}

static inline void bp()
{
//    printf("Breakpoint reached at 0x%x\n", c_cur);
//    printf("Call stack depth: %i\n", call_st_cur + 1);
//    printf("Stack depth: %i\n", st_cur + 1);
//    printf("Stack content:\n");
//    int i;
//    for (i = st_cur; i >= 0; i--)
//        printf("    0x%x\n", stack[i]);
//    printf("Press enter to continue\n");
//    getchar();
}

#endif // MACHINE_H_INCLUDED
