#include "machine.h"


Machine machine;

void machine_initialize()
{
    machine.memory_end = machine.machine_memory + DEVICE_MEMORY_SIZE;
    machine.stack_end = machine.machine_stack + STACK_SIZE;
    machine.stack_first = machine.machine_stack+1;
    machine.call_first = machine.machine_stack+1;
    machine.var_number = 0;
    machine.progam_cursor_mask = 0xFFF;
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

 void push() //+
{
    increment_program_ptr(); //push is followed by one byte, so increment to skip argument
    increment_stack_cursor();
    *machine.machine_stack = *machine.machine_memory;
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
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) + *machine.stack_ptr;
}
 void sub() //+

{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) - *machine.stack_ptr;
}
 void mult() //+
{

#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
    *(machine.stack_ptr-1) = *(machine.stack_ptr-1) * (*machine.stack_ptr);

}
 void divide()

{
#ifdef MEMORY_CHECKS_ENABLED
    if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
        halt();
#endif // MEMORY_CHECKS_ENABLED
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

    increment_stack_cursor();
    *machine.stack_ptr = *(machine.program_ptr + *machine.program_ptr);
}

 void tomm() //8
{
    increment_program_ptr();
#ifdef MEMORY_CHECKS_ENABLED
    if (machine.program_ptr >= machine.memory_end)
        halt("Segmentation fault after tomem");
#endif // MEMORY_CHECKS_ENABLED
    *(machine.machine_memory + *machine.program_ptr) = *machine.stack_ptr;
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

 void dup()
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
 void succ_exit() {;}
 void  quit()
{
    succ_exit();
}

 void bp()
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
