#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED

#include "global.h"
#include "variable.h"
#include "label.h"

#include <stdio.h>
#include <stdlib.h>
#define DEVICE_MEMORY_SIZE  4096

#define LABEL_MEMORY_SIZE 512
#define DEVICE_VAR_SIZE 64
#define STACK_SIZE 2048

#define SHADOW_MEMORY DEVICE_MEMORY_SIZE

#define MEMORY_CHECKS_ENABLED // disable this to save processing time. might result in aegmentation fault.
typedef struct
{

    variable variables[VARIABLE_MEMORY_SIZE];
    variable* variable_ptr;

    label progam_labels[MAX_LABELS];
    label* label_ptr;

    DWORD* exec_ptr;
    DWORD machine_memory[DEVICE_MEMORY_SIZE];
    DWORD variable_memory[DEVICE_VAR_SIZE];
    DWORD* variable_memory_ptr;
    DWORD* memory_end;
    DWORD* stack_end;
    DWORD* stack_first;
    DWORD* stack_second;
    DWORD* call_stack_end;
    DWORD* call_first;
    DWORD* section_var;
    DWORD* section_str;
    DWORD machine_call_stack[STACK_SIZE];
    DWORD machine_stack[STACK_SIZE]; //first value will always be 0 and treated as empty stack

    DWORD progam_cursor_mask;
    DWORD* program_ptr;
    DWORD lablel_number;

    DWORD* stack_ptr;
    DWORD* call_ptr;


    BOOL flag_eq;
    BOOL flag_gr;
    DWORD var_number;

    long long ticks;
} Machine;

Machine machine;

void machine_load(char* filename, Machine* mac);
void machine_initialize();
void read_inputs();
void update_outputs();


void halt() ;

void increment_program_ptr();

void increment_stack_cursor() ;
void decrement_stack_cursor() ;
void push() ;
void pop();
void add() ;
void sub() ;
void mult();
void divide();
void jmp(); //+;
void cmp(); // lower is grater;


void je(); /// jump if equal, 8byte (skip one byte);

void jne() ;

void jl();
void jg();

void jle();
void jge();

void frmm(); //8;

void tomm(); //8;

void sfrommem(); //8;
void stomem(); //8;
void afrom(); //8;

void atom() ;

void call();

void ret();
void dup();

void randint();

void swap();
void stinc();
void stdec();
void inc();
void dec();
void sttoar();
void artost();

void land();
void lor();
void lxor();
void lnot();

void band();
void bor();
void bxor();
void bnot();

void nop();
void succ_exit();
void  quit();
void bp();

#endif // MACHINE_H_INCLUDED
