# microvm todo

## version 0.2.2
- [ ] make toptr and ptr two two byte commands in order to have possibility to switch to 16 bit opcodes.
## version 0.2.1
- [x] test arrays,
- [x] add $define
- [ ] add $include 
## version 0.2.0
- [x] add stack backup command $backup <-> $reset
- [] add two pass compiling in order to have dynamic memory allocation targeting smaller boards.
- [] change DWORD to TYPE, in order to change 32 <> 16 bit with one define.
## version 0.1.0
- [x] test labels.
- [ ] Add memory checks for array element addressing.
- [ ] Make project portable between xc32 and gcc.
- [x] write tests.
- [ ] write a make file as an alterative to codeblocks.
- [ ] cover complete opcode set in test.
- [x] add assert opcode for semi automated testing.
