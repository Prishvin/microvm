# Change Log
All notable changes to this project will be documented in this file.

## [status - unreleased]
## [0.2.4]
-$include added for compiling several files. Usage: $include <full path>
## [0.2.3]
-all conditional jumps tested. 
-opcode order changed.
-some tests added
-input, rst, clr instruction added
## [0.2.2]
-toptr, ptro commands added. These commands operate with RAM memory of host device.
-assert added. Assert ensures top two values on stack are equal.
-errno added to each perror

## [0.2.1]
-not all opcodes are tested.  
-compilation errors are handled. Compilation is interrupted when unexpected input found.  
-preprocessor $define statement added. $define works similar to C/C++ #define.  

## [0.2.0]
-not all opcodes are tested.
-interpreter, compiler and machine pass simple test located in test folder. 

## [0.1.0]
-minimal data element is 4 bytes. this project aims 32bit systems. Although can be easily ported to 16bit. 8 bit operation is not planned.  
-interpreter commands tested: push, pop, var, add, mul, div, sub, and, or, not, binary and, binary or, binary not.  
-cli commands tested: $clear, $reset, $stack.   

