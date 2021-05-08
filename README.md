# microvm
## version 0.1.0
The aim of this project is to create a stack based language and virtual machine for microcontrollers. A mix of approaches is used. 
Separate memory is used for program and variable space (Harvard architecture). An interpreter, virtual machine and compiler are available. A demostration of the interpreter in action is presented below.

use **codeblocks 16.01**  and **GCC** to build.  Make file work in progress.

for vm code look at **machine.h**, machine.c
compiler code can be found in **compiler.h**, compiler.c

currently this code is distributed under **GNU AGPLv3.** or commercial license upon request.


https://user-images.githubusercontent.com/371566/117532644-894a5680-aff9-11eb-95a3-7eef6805b61d.mp4

The interpreter code snipped is presented on Block 1. The VM loops through the available opcodes until in reaches QUIT opcode or program memory bounds. A function corresponding to the opcode (see table 1), is called.
```C
            DWORD *ptr = machine.program_ptr;
            DWORD op = *ptr;
            DWORD qt = opcodes_find("QUIT");
            while(TRUE)
            {
                op = *ptr;         
                if(op>=qt || *ptr>=machine.memory_end)
                {
                    if(op==qt )
                    {
                        printf("[SUCCESS] program executed.");
                    }
                    else
                    {
                        perror("[FATAL] Abnormal termination");
                    }
                    break;
                }
                (opcodes[*ptr].ptr)();
                ptr++;
            }
```
Block 1

An example implementation of such functions are shown in Block 2.
```C
            void push() 
            {
                increment_program_ptr(); //push is followed by one byte, so increment to skip argument
                *machine.stack_ptr = *machine.program_ptr;
                increment_stack_cursor();
                increment_program_ptr();
            }
            void pop()
            {
                decrement_stack_cursor();
            }
            void add() 
            {
            #ifdef MEMORY_CHECKS_ENABLED
                if(machine.stack_ptr < machine.stack_second || machine.stack_ptr >= machine.stack_end)
                    halt();
            #endif // MEMORY_CHECKS_ENABLED
                machine.stack_ptr--;
                *(machine.stack_ptr-1) = *(machine.stack_ptr-1) + *machine.stack_ptr;
            }
```
Block 2



Available commands are listed below.
|   opcode |  Mnemonics |      description |
|----------|------------|-----------------------------------------------------------------------|
|     0  |  NOP      |       no operation 4 byte <BR>								|
|     1  |  PUSH     |      push to stack  <BR>                                                 |
|     2  |  POP      |       pop from stack                                                     |
|     3  |  ADD      |       add two values on stack                                            |
|     4  |  SUB      |       subtact top value from previos                                     |
|     5  |  MUL      |       multiply two values|                                               |
|     6  |  DIV      |       divied two values|                                                 |
|     7  |  BXOR     |       last opcode                                                        |
|     8  |  JMP      |       unconditional jump to label                                        |
|     9  |  JE       |       jump if equal                                                      |
|     10 |  JL       |       jump if less                                                       |
|     11 |  JG       |       jump if greater                                                    |
|     12 |  JNE      |       jump if not eq                                                     |
|     13 |  JLE      |       jump if not less                                                   |
|     14 |  JGE      |       jump if not greter                                                 |
|     15 |  FRMM     |       from memory address to stack                                       |
|     16 |  TOMM     |       from stack to memory                                               |
|     17 |  RFRMM    |       from memory adress defined by stack                                |
|     18 |  RTOMM    |       to memory adress defined by stack                                  |
|     19 |  CALL     |       call label                                                         |
|     20 |  RET      |       return from call                                                   |
|     21 |  DUP      |       duplicate stack value                                              |
|     22 |  SWAP     |       swap two stack values                                              |
|     23 |  INC      |       increment top stack value                                          |
|     24 |  DEC      |       decrement top stack value                                          |
|     25 |  AFRMM    |       array not implemented                                              |
|     26 |  ATOMM    |       array not implemented                                              |
|     27 |  BP       |       breakpoint not implemented                                         |
|     28 |  CMP      |       compare top two stack values| place result in flag_gr and flag_eq  |
|     29 |  PRINT    |                                                                          |
|     30 |  DELAY    |                                                                          |
|     31 |  STATE    |                                                                          |
|     32 |  AND      |                                                                          |
|     33 |  OR       |                                                                          |
|     34 |  NOT      |                                                                          |
|     35 |  XOR      |                                                                          |
|     36 |  BAND     |                                                                          |
|     37 |  BOR      |                                                                          |
|     38 |  BNOT     |                                                                          |
|     39 |  QUIT     |                                                                          |

Table. 1.
      
example program is presented in simple|p
