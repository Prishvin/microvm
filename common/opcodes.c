#include "opcodes.h"
void initialize_opcodes()
{


    Opcode* ptr = opcodes;
    *ptr++= (Opcode){.opcode = 0, .txt = "NOP"};
    *ptr++= (Opcode){.opcode = 1, .txt = "PUSH"};
    *ptr++= (Opcode){.opcode = 2, .txt = "POP"};
    *ptr++= (Opcode){.opcode = 3, .txt = "ADD"};
    *ptr++= (Opcode){.opcode = 4, .txt = "SUB"};
    *ptr++= (Opcode){.opcode = 5, .txt = "MUL"};
    *ptr++= (Opcode){.opcode = 6, .txt = "DIV"};
    *ptr++= (Opcode){.opcode = 7, .txt = "QUIT"};
    *ptr++= (Opcode){.opcode = 8, .txt = "JMP"};
    *ptr++= (Opcode){.opcode = 9, .txt = "JE"};
    *ptr++= (Opcode){.opcode = 10, .txt = "JL"};
    *ptr++= (Opcode){.opcode = 11, .txt = "JG"};
    *ptr++= (Opcode){.opcode = 12, .txt = "JNE"};
    *ptr++= (Opcode){.opcode = 13, .txt = "JLE"};
    *ptr++= (Opcode){.opcode = 14, .txt = "JGE"};
    *ptr++= (Opcode){.opcode = 15, .txt = "FRMM"};
    *ptr++= (Opcode){.opcode = 16, .txt = "TOMM"};
    *ptr++= (Opcode){.opcode = 17, .txt = "RFRMM"};
    *ptr++= (Opcode){.opcode = 18, .txt = "ROMM"};
    *ptr++= (Opcode){.opcode = 19, .txt = "CALL"};
    *ptr++= (Opcode){.opcode = 20, .txt = "RET"};
    *ptr++= (Opcode){.opcode = 21, .txt = "DUP"};
    *ptr++= (Opcode){.opcode = 22, .txt = "SWAP"};
    *ptr++= (Opcode){.opcode = 23, .txt = "INC"};
    *ptr++= (Opcode){.opcode = 24, .txt = "DEC"};
    *ptr++= (Opcode){.opcode = 25, .txt = "BP"};
}
