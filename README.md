# vm
The aim of this project is to created a stack based language and virtual machine for microcontrollers. A mix of approaches is used. Available commands are listed below.

opcode   Mnemonics
.     0    NOP            // no operation 4 byte <BR>
.     1    PUSH           // push to stack  <BR>
.     2    POP            // pop from stack
.     3    ADD            // add two values on stack
.     4    SUB            // subtact top value from previos
.     5    MUL            // multiply two values.
.     6    DIV            // divied two values.
.     7    QUIT           // last opcode
.     8    JMP            // unconditional jump to label
.     9    JE             // jump if equal
.     10   JL             // jump if less
.     11   JG             // jump if greater
.     12   JNE            // jump if not eq
.     13   JLE            // jump if not less
.     14   JGE            // jump if not greter
.     15   FRMM           // from memory address to stack
.     16   TOMM           // from stack to memory
.     17   RFRMM          //from memory adress defined by stack
.     18   RTOMM          //to memory adress defined by stack
.     19   CALL           // call label
.     20   RET            //return from call
.     21   DUP            // duplicate stack value
.     22   SWAP           // swap two stack values
.     23   INC            // increment top stack value
.     24   DEC            // decrement top stack value
.     25   AFRMM          // array not implemented
.     26   ATOMM          // array not implemented
.     27   BP             // breakpoint not implemented
.     28   CMP            //compare top two stack values. place result in flag_gr and flag_eq
.     29   PRINT          //
.     30   DELAY          //
.     31   STATE          //
.     32   AND            //
.     33   OR             //
.     34   NOT            //
.     35   XOR            //
.     36   BAND           //
.     37   BOR            //
.     38   BNOT           //
.     39   BXOR           //
    
      
example program is presented in simple.p
