push 1
push 5
var dcr
var v2
var v3
var v4
push 2
TOMM v4
pop
call label2
:label
FRMM v4
call func1
sub
cmp
jle label
push 0
quit
:func1
pop
push 1
ret
:label2
dup
mul
ret
