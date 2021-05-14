#include "opcodes.h"


DWORD PUSHOP = 1;

void initialize_opcodes()
{


    Opcode* p = opcodes;
    *p++= (Opcode){.opcode = 0, .txt = "NOP",.ptr       =  nop,     .sz = 0 };
    *p++= (Opcode){.opcode = 1, .txt = "PUSH",.ptr      =  push,    .sz = 0 };
    *p++= (Opcode){.opcode = 2, .txt = "POP",.ptr       =  pop,     .sz = 1 };
    *p++= (Opcode){.opcode = 3, .txt = "ADD",.ptr       =  add,     .sz = 2};
    *p++= (Opcode){.opcode = 4, .txt = "SUB",.ptr       =  sub,     .sz = 2};
    *p++= (Opcode){.opcode = 5, .txt = "MUL",.ptr       =  mult,    .sz = 2};
    *p++= (Opcode){.opcode = 6, .txt = "DIV",.ptr       =  divide,  .sz = 2};
    *p++= (Opcode){.opcode = 7, .txt = "JMP",.ptr       =  jmp,     .sz = 0};
    *p++= (Opcode){.opcode = 8, .txt = "JE",.ptr        =  je,      .sz = 0};
    *p++= (Opcode){.opcode = 9, .txt = "JL",.ptr        =  jl,      .sz = 0};
    *p++= (Opcode){.opcode = 10, .txt = "JG",.ptr       =  jg,      .sz = 0};
    *p++= (Opcode){.opcode = 11, .txt = "JNE",.ptr      =  jne,     .sz = 0};
    *p++= (Opcode){.opcode = 12, .txt = "JLE",.ptr      =  jle,     .sz = 0};
    *p++= (Opcode){.opcode = 13, .txt = "JGE",.ptr      =  jge,     .sz = 0};
    *p++= (Opcode){.opcode = 14, .txt = "FRMM",.ptr     =  frmm,    .sz = 0};
    *p++= (Opcode){.opcode = 15, .txt = "TOMM",.ptr     =  tomm,    .sz = 1};
    *p++= (Opcode){.opcode = 16, .txt = "RFRMM",.ptr    =  sfrommem,.sz = 1};
    *p++= (Opcode){.opcode = 17, .txt = "RTOMM",.ptr    =  stomem,  .sz = 2};
    *p++= (Opcode){.opcode = 18, .txt = "CALL",.ptr     =  call,    .sz = 0};
    *p++= (Opcode){.opcode = 19, .txt = "RET",.ptr      =  ret,     .sz = 0};
    *p++= (Opcode){.opcode = 20, .txt = "DUP",.ptr      =  duplicate,.sz = 1};
    *p++= (Opcode){.opcode = 22, .txt = "SWAP",.ptr     =  swap,    .sz = 2};
    *p++= (Opcode){.opcode = 22, .txt = "INC",.ptr      =  inc,     .sz = 1};
    *p++= (Opcode){.opcode = 23, .txt = "DEC",.ptr      =  dec,     .sz = 1};
    *p++= (Opcode){.opcode = 24, .txt = "AFROM",.ptr    =  afrom,   .sz = 1};
    *p++= (Opcode){.opcode = 25, .txt = "ATOM",.ptr     =  atom,    .sz = 2};
    *p++= (Opcode){.opcode = 26, .txt = "BP",.ptr       =  bp,      .sz = 0};
    *p++= (Opcode){.opcode = 27, .txt = "CMP",.ptr      =  cmp,     .sz = 2};
    *p++= (Opcode){.opcode = 28, .txt = "PRINT",.ptr    =  aprint,  .sz = 2};
    *p++= (Opcode){.opcode = 29, .txt = "DELAY",.ptr    =  adelay,  .sz = 1};
    *p++= (Opcode){.opcode = 30, .txt = "STATE",.ptr    =  astate,  .sz = 0};
    *p++= (Opcode){.opcode = 31, .txt = "AND",.ptr      =  land,    .sz = 2};
    *p++= (Opcode){.opcode = 32, .txt = "OR",.ptr       =  lor,     .sz = 2};
    *p++= (Opcode){.opcode = 33, .txt = "NOT",.ptr      =  lnot,    .sz = 1};
    *p++= (Opcode){.opcode = 34, .txt = "XOR",.ptr      =  lxor,    .sz = 2};
    *p++= (Opcode){.opcode = 35, .txt = "BAND",.ptr     =  band,     .sz = 2};
    *p++= (Opcode){.opcode = 36, .txt = "BOR",.ptr      =  bor,      .sz = 2};
    *p++= (Opcode){.opcode = 37, .txt = "BNOT",.ptr     =  bnot,     .sz = 1};
    *p++= (Opcode){.opcode = 38, .txt = "BXOR",.ptr     = bxor ,     .sz = 2};
    *p++= (Opcode){.opcode = 39, .txt = "ASSERT",.ptr   =  asrt,     .sz = 2};
    *p++= (Opcode){.opcode = 40, .txt = "PTRTO",.ptr    =  ptrto,    .sz = 0};
    *p++= (Opcode){.opcode = 41, .txt = "TOPTR",.ptr    =  toptr,    .sz = 1};
    *p++= (Opcode){.opcode = 42, .txt = "QUIT",.ptr     =  quit,     .sz = 1};

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
