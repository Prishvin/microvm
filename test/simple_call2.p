push 1
push 20
var dcr
var v2
var v3
var v4
push 2
TOMM v4
call label2
pop
pop
:label
FRMM v4
call func1
sub
cmp
jle label
quit
:func1
pop
push 1
ret
:label2
dup
mul
ret
