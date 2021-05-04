# vm
This project consists of a virtual machine and a compiler for a simple Forth like stack based language.
current command set is

Simple.p is a demo program counting from 20 to 1 by step 2

machine functions defined by machine.h

compiler is in StackCompuler folder.

project files yet to be organized.

    *ptr++= (Opcode){.opcode = 0, .txt = "NOP"};    // no operation
    *ptr++= (Opcode){.opcode = 1, .txt = "PUSH"};   // push to stack
    *ptr++= (Opcode){.opcode = 2, .txt = "POP"};    // pop from stack
    *ptr++= (Opcode){.opcode = 3, .txt = "ADD"};    // add two values on stack
    *ptr++= (Opcode){.opcode = 4, .txt = "SUB"};    // subtact top value from previos
    *ptr++= (Opcode){.opcode = 5, .txt = "MUL"};    // multiply two values.
    *ptr++= (Opcode){.opcode = 6, .txt = "DIV"};    // divied two values.
    *ptr++= (Opcode){.opcode = 7, .txt = "QUIT"};   // last opcode
    *ptr++= (Opcode){.opcode = 8, .txt = "JMP"};    // unconditional jump to label
    *ptr++= (Opcode){.opcode = 9, .txt = "JE"};     // jump if equal
    *ptr++= (Opcode){.opcode = 10, .txt = "JL"};    // jump if less
    *ptr++= (Opcode){.opcode = 11, .txt = "JG"};    // jump if greater
    *ptr++= (Opcode){.opcode = 12, .txt = "JNE"};   // jump if not eq
    *ptr++= (Opcode){.opcode = 13, .txt = "JLE"};   // jump if not less
    *ptr++= (Opcode){.opcode = 14, .txt = "JGE"};   // jump if not greter
    *ptr++= (Opcode){.opcode = 15, .txt = "FRMM"};  // from memory address to stack
    *ptr++= (Opcode){.opcode = 16, .txt = "TOMM"};  // from stack to memory
    *ptr++= (Opcode){.opcode = 17, .txt = "RFRMM"}; //from memory adress defined by stack
    *ptr++= (Opcode){.opcode = 18, .txt = "RTOMM"}; //to memory adress defined by stack
    *ptr++= (Opcode){.opcode = 19, .txt = "CALL"};  // call label
    *ptr++= (Opcode){.opcode = 20, .txt = "RET"};   //return from call
    *ptr++= (Opcode){.opcode = 21, .txt = "DUP"};   // duplicate stack value
    *ptr++= (Opcode){.opcode = 22, .txt = "SWAP"};  // swap two stack values
    *ptr++= (Opcode){.opcode = 23, .txt = "INC"};   // increment top stack value
    *ptr++= (Opcode){.opcode = 24, .txt = "DEC"};   // decrement top stack value
    *ptr++= (Opcode){.opcode = 25, .txt = "AFRMM"}; // array not implemented
    *ptr++= (Opcode){.opcode = 26, .txt = "ATOMM"}; // array not implemented
    *ptr++= (Opcode){.opcode = 27, .txt = "BP"};    // breakpoint not implemented
