push 1
push 10
:label
push 1
sub
cmp
je lb_exit
jmp label
:lb_exit
push 0
quit
:label2
dup
mul
pop
ret
