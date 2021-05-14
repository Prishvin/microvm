# microvm
## version 0.2.2
The aim of this project is to create a stack based language and virtual machine for microcontrollers. A mix of approaches is used. 
Separate memory is used for program and variable space (Harvard architecture). An interpreter, virtual machine and compiler are available. A demostration of the interpreter in action is presented below.

use **codeblocks 16.01**  and **GCC** to build.  Make file work in progress.

for vm code look at **machine.h**, machine.c
compiler code can be found in **compiler.h**, compiler.c

currently this code is distributed under **GNU AGPLv3.** or commercial license upon request.

**This project is inspired by a work by Aleksei Udalov: https://github.com/aleksei-udalov/vm.git**


https://user-images.githubusercontent.com/371566/117532644-894a5680-aff9-11eb-95a3-7eef6805b61d.mp4

## example microvm code
```asm
$define _maxbound 30
push _maxbound
pop
push 1
push _maxbound
var dcr
var v2
var v3
var v4
push 2
TOMM v4
pop
:label
FRMM v4
sub
cmp
jle label
quit

```
## microvm usage

-interpreter mode>    microvm **-i**              
-compile source file> microvm **-c** source destination             
-run script>          microvm **-r**  binary              
-display help>        microvm **-h**                        
            
## interpreter commands
The interperter commands can be used in interactive mode to display or control vm state. A command should be preceded by a '$' sign.

-**$stack**      - displays stack contents.     
-**$var**        - displays all vars.           
-**$clear**      - clears screen    
-**$reset**      - resets vm        
-**$backup**     - creates a copy of vm memory.                         
-**$restore**       - restores memory from a backup.           


## interpreter loop
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

## opcodes

Available commands are listed below. Length is give in opcode count including arguments.

|status|opcode |Mnemonics  |Length   |                           description                              |
|------|-------|-----------|---------|--------------------------------------------------------------------|
|&#9745; |    0  |  NOP      |   1     | no operation 4 byte <BR>	                                          |
|&#9745; |    1  |  PUSH     |   2     | push to stack  <BR>                                                |
|&#9745; |    2  |  POP      |   1     | pop from stack                                                     |
|&#9745; |    3  |  ADD      |   1     | add two values on stack                                            |
|&#9745; |    4  |  SUB      |   1     | subtact top value from previos                                     |
|&#9745; |    5  |  MUL      |   1     | multiply two values|                                               |
|&#9745; |    6  |  DIV      |   1     | divied two values|                                                 |
|&#9745; |    7  |  BXOR     |   1     | last opcode                                                        |
|&#9745; |    8  |  JMP      |   2     | unconditional jump to label                                        |
|&#9744; |    9  |  JE       |   2     | jump if equal                                                      |
|&#9744; |    10 |  JL       |   2     | jump if less                                                       |
|&#9744; |    11 |  JG       |   2     | jump if greater                                                    |
|&#9744; |    12 |  JNE      |   2     | jump if not eq                                                     |
|&#9745; |    13 |  JLE      |   2     | jump if not less                                                   |
|&#9744; |    14 |  JGE      |   2     | jump if not greter                                                 |
|&#9745; |    15 |  FRMM     |   2     | from memory address to stack                                       |
|&#9745; |    16 |  TOMM     |   2     | from stack to memory                                               |
|&#9744; |    17 |  -----    |         | reserved                                                           |
|&#9744; |    18 |  -----    |         | reserved                                                           |
|&#9745; |    19 |  CALL     |   2     | call label                                                         |
|&#9745; |    20 |  RET      |   1     | return from call                                                   |
|&#9745; |    21 |  DUP      |   1     | duplicate stack value                                              |
|&#9745; |    22 |  SWAP     |   1     | swap two stack values                                              |
|&#9745; |    23 |  INC      |   1     | increment top stack value                                          |
|&#9745; |    24 |  DEC      |   1     | decrement top stack value                                          |
|&#9745; |    25 |  AFRMM    |   2     | from array to stack                                                |
|&#9745; |    26 |  ATOMM    |   2     | from stack to array                                                |
|&#9745; |    27 |  BP       |   1     | breakpoint not implemented                                         |
|&#9745; |    28 |  CMP      |   1     | compare top two stack values| place result in flag_gr and flag_eq  |
|&#9745; |    29 |  PRINT    |   1     | prints top stack value                                             |
|&#9744; |    30 |  DELAY    |   2     | delay in ms                                                        |
|&#9745; |    31 |  STATE    |   1     | prints current state (depricated)                                  |
|&#9745; |    32 |  AND      |   1     | logical and                                                        |
|&#9745; |    33 |  OR       |   1     | logical or                                                         |
|&#9745; |    34 |  NOT      |   1     | logical not                                                        |
|&#9745; |    35 |  XOR      |   1     | binary xor                                                         |
|&#9745; |    36 |  BAND     |   1     | binary and                                                         |
|&#9745; |    37 |  BOR      |   1     | binary or                                                          |
|&#9745; |    38 |  BNOT     |   1     | binary not                                                         |
|&#9745; |    39 |  ASSERT   |   1     | asserts top two values on stack are equal.                         |
|&#9745; |    40 |  PTRTO    |   2     | reads from host pointer to top stack                               |
|&#9745; |    41 |  TOPTR    |   2     | writes top stack to host pointer                                   |
|&#9745; |    42 |  QUIT     |   1     | finalize program                                                   |


Table. 1.
      
example program is presented in simple|p
