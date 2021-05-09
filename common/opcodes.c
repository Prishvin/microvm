#include "opcodes.h"

void initialize_opcodes()
{


    Opcode* p = opcodes;
    *p++= (Opcode){.opcode = 0, .txt = "NOP",.ptr =  nop};
    *p++= (Opcode){.opcode = 1, .txt = "PUSH",.ptr =  push};
    *p++= (Opcode){.opcode = 2, .txt = "POP",.ptr =  pop};
    *p++= (Opcode){.opcode = 3, .txt = "ADD",.ptr =  add};
    *p++= (Opcode){.opcode = 4, .txt = "SUB",.ptr =  sub};
    *p++= (Opcode){.opcode = 5, .txt = "MUL",.ptr =  mult};
    *p++= (Opcode){.opcode = 6, .txt = "DIV",.ptr =  divide};
    *p++= (Opcode){.opcode = 7, .txt = "BXOR",.ptr = bxor };
    *p++= (Opcode){.opcode = 8, .txt = "JMP",.ptr =  jmp};
    *p++= (Opcode){.opcode = 9, .txt = "JE",.ptr =  je};
    *p++= (Opcode){.opcode = 10, .txt = "JL",.ptr =  jl};
    *p++= (Opcode){.opcode = 11, .txt = "JG",.ptr =  jg};
    *p++= (Opcode){.opcode = 12, .txt = "JNE",.ptr =  jne};
    *p++= (Opcode){.opcode = 13, .txt = "JLE",.ptr =  jle};
    *p++= (Opcode){.opcode = 14, .txt = "JGE",.ptr =  jge};
    *p++= (Opcode){.opcode = 15, .txt = "FRMM",.ptr =  frmm};
    *p++= (Opcode){.opcode = 16, .txt = "TOMM",.ptr =  tomm};
    *p++= (Opcode){.opcode = 17, .txt = "RFRMM",.ptr =  sfrommem};
    *p++= (Opcode){.opcode = 18, .txt = "RTOMM",.ptr =  stomem};
    *p++= (Opcode){.opcode = 19, .txt = "CALL",.ptr =  call};
    *p++= (Opcode){.opcode = 20, .txt = "RET",.ptr =  ret};
    *p++= (Opcode){.opcode = 21, .txt = "DUP",.ptr =  adup};
    *p++= (Opcode){.opcode = 22, .txt = "SWAP",.ptr =  swap};
    *p++= (Opcode){.opcode = 23, .txt = "INC",.ptr =  inc};
    *p++= (Opcode){.opcode = 24, .txt = "DEC",.ptr =  dec};
    *p++= (Opcode){.opcode = 25, .txt = "AFRMM",.ptr =  afrom};
    *p++= (Opcode){.opcode = 26, .txt = "ATOMM",.ptr =  atom};
    *p++= (Opcode){.opcode = 27, .txt = "BP",.ptr =  bp};
    *p++= (Opcode){.opcode = 28, .txt = "CMP",.ptr =  cmp};
    *p++= (Opcode){.opcode = 29, .txt = "PRINT",.ptr =  aprint};
    *p++= (Opcode){.opcode = 30, .txt = "DELAY",.ptr =  adelay};
    *p++= (Opcode){.opcode = 31, .txt = "STATE",.ptr =  astate};
    *p++= (Opcode){.opcode = 32, .txt = "AND",.ptr =  land};
    *p++= (Opcode){.opcode = 33, .txt = "OR",.ptr =  lor};
    *p++= (Opcode){.opcode = 34, .txt = "NOT",.ptr =  lnot};
    *p++= (Opcode){.opcode = 35, .txt = "XOR",.ptr =  lxor};
    *p++= (Opcode){.opcode = 36, .txt = "BAND",.ptr =  band};
    *p++= (Opcode){.opcode = 37, .txt = "BOR",.ptr =  bor};
    *p++= (Opcode){.opcode = 38, .txt = "BNOT",.ptr =  bnot};
    *p++= (Opcode){.opcode = 39, .txt = "QUIT",.ptr =  quit};

    machine.total_opcodes = 40;
}

DWORD opcodes_find(char* txt)
{
     DWORD result = TOKEN_UNKNOWN;
     BYTE i;
     for(i = 0; i < MAX_OPCODES; i++)
     {
        if(strcmp(txt, opcodes[i].txt) == 0)
            result = opcodes[i].opcode;
     }

     return result;
}
