# vm
The aim of this project is to created a stack based language and virtual machine for microcontrollers. A mix of approaches is used. Available commands are listed below.

opcode   Mnemonics
1.     0    NOP            // no operation 4 byte <BR>
2.     1    PUSH           // push to stack  <BR>
2.     2    POP            // pop from stack
2.     3    ADD            // add two values on stack
2.     4    SUB            // subtact top value from previos
2.     5    MUL            // multiply two values.
2.     6    DIV            // divied two values.
2.     7    QUIT           // last opcode
2.     8    JMP            // unconditional jump to label
2.     9    JE             // jump if equal
2.     10   JL             // jump if less
2.     11   JG             // jump if greater
2.     12   JNE            // jump if not eq
2.     13   JLE            // jump if not less
2.     14   JGE            // jump if not greter
2.     15   FRMM           // from memory address to stack
2.     16   TOMM           // from stack to memory
2.     17   RFRMM          //from memory adress defined by stack
2.     18   RTOMM          //to memory adress defined by stack
2.     19   CALL           // call label
2.     20   RET            //return from call
2.     21   DUP            // duplicate stack value
2.     22   SWAP           // swap two stack values
2.     23   INC            // increment top stack value
2.     24   DEC            // decrement top stack value
2.     25   AFRMM          // array not implemented
2.     26   ATOMM          // array not implemented
2.     27   BP             // breakpoint not implemented
2.     28   CMP            //compare top two stack values. place result in flag_gr and flag_eq
2.     29   PRINT          //
2.     30   DELAY          //
2.     31   STATE          //
2.     32   AND            //
2.     33   OR             //
2.     34   NOT            //
2.     35   XOR            //
2.     36   BAND           //
2.     37   BOR            //
2.     38   BNOT           //
2.     39   BXOR           //
     
      
example program is presented in simple.p
