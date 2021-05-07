# vm
The aim of this project is to created a stack based language and virtual machine for microcontrollers. A mix of approaches is used. Available commands are listed below.

     0   NOP    // no operation 4 byte
     1   PUSH   // push to stack 
     2   POP    // pop from stack
     3   ADD    // add two values on stack
     4   SUB    // subtact top value from previos
     5   MUL    // multiply two values.
     6   DIV    // divied two values.
     7   QUIT   // last opcode
     8   JMP    // unconditional jump to label
     9   JE     // jump if equal
     10   JL    // jump if less
     11   JG    // jump if greater
     12   JNE   // jump if not eq
     13   JLE   // jump if not less
     14   JGE   // jump if not greter
     15   FRMM  // from memory address to stack
     16   TOMM  // from stack to memory
     17   RFRMM //from memory adress defined by stack
     18   RTOMM //to memory adress defined by stack
     19   CALL  // call label
     20   RET   //return from call
     21   DUP   // duplicate stack value
     22   SWAP  // swap two stack values
     23   INC   // increment top stack value
     24   DEC   // decrement top stack value
     25   AFRMM // array not implemented
     26   ATOMM // array not implemented
     27   BP    // breakpoint not implemented
     28 CMP  cmp//
     29 PRINT  cmp
     30 DELAY  cmp
     31 STATE  cmp

     32 AND  land
     33 OR  lor
     34 NOT  lnot
     35 XOR  lxor
     36 BAND  band
     37 BOR  bor
     38 BNOT  bnot
     39 BXOR  bxor
     
     
example program is presented in simple.p
