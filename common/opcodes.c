#include "opcodes.h"

void initialize_opcodes()
{


    Opcode* ptr = opcodes;
    *ptr++= (Opcode){.opcode = 0, .txt = "NOP", ptr =  nop};
    *ptr++= (Opcode){.opcode = 1, .txt = "PUSH", ptr =  push};
    *ptr++= (Opcode){.opcode = 2, .txt = "POP", ptr =  pop};
    *ptr++= (Opcode){.opcode = 3, .txt = "ADD", ptr =  add};
    *ptr++= (Opcode){.opcode = 4, .txt = "SUB", ptr =  sub};
    *ptr++= (Opcode){.opcode = 5, .txt = "MUL", ptr =  mult};
    *ptr++= (Opcode){.opcode = 6, .txt = "DIV", ptr =  divide};
    *ptr++= (Opcode){.opcode = 7, .txt = "QUIT", ptr =  quit};
    *ptr++= (Opcode){.opcode = 8, .txt = "JMP", ptr =  jmp};
    *ptr++= (Opcode){.opcode = 9, .txt = "JE", ptr =  je};
    *ptr++= (Opcode){.opcode = 10, .txt = "JL", ptr =  jl};
    *ptr++= (Opcode){.opcode = 11, .txt = "JG", ptr =  jg};
    *ptr++= (Opcode){.opcode = 12, .txt = "JNE", ptr =  jne};
    *ptr++= (Opcode){.opcode = 13, .txt = "JLE", ptr =  jle};
    *ptr++= (Opcode){.opcode = 14, .txt = "JGE", ptr =  jge};
    *ptr++= (Opcode){.opcode = 15, .txt = "FRMM", ptr =  frmm};
    *ptr++= (Opcode){.opcode = 16, .txt = "TOMM", ptr =  tomm};
    *ptr++= (Opcode){.opcode = 17, .txt = "RFRMM", ptr =  sfrommem};
    *ptr++= (Opcode){.opcode = 18, .txt = "RTOMM", ptr =  stomem};
    *ptr++= (Opcode){.opcode = 19, .txt = "CALL", ptr =  call};
    *ptr++= (Opcode){.opcode = 20, .txt = "RET", ptr =  ret};
    *ptr++= (Opcode){.opcode = 21, .txt = "DUP", ptr =  dup};
    *ptr++= (Opcode){.opcode = 22, .txt = "SWAP", ptr =  swap};
    *ptr++= (Opcode){.opcode = 23, .txt = "INC", ptr =  inc};
    *ptr++= (Opcode){.opcode = 24, .txt = "DEC", ptr =  dec};
    *ptr++= (Opcode){.opcode = 25, .txt = "AFRMM", ptr =  afrom};
    *ptr++= (Opcode){.opcode = 26, .txt = "ATOMM", ptr =  atom};
    *ptr++= (Opcode){.opcode = 27, .txt = "BP", ptr =  bp};
    *ptr++= (Opcode){.opcode = 28, .txt = "CMP", ptr =  cmp};
}

DWORD opcodes_find(char* txt)
{
     DWORD result = 0;
     BYTE i;
     for(i = 0; i < MAX_OPCODES; i++)
     {
        if(strcmp(txt, opcodes[i].txt) == 0)
            result = opcodes[i].opcode;
     }

     return result;
}
