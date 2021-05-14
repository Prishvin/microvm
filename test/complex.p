nop
push 10
pop
push 5
push 5
add
push 10
assert
clr
push 2
push 25
mul
push 50
assert
clr
push 20
push 2
div
push 10
assert
clr
push 10
push 20
cmp
je lb1
clr
:lb1
push 20
push 10
sub
push 10
cmp
je lb2
push 1
quit
:lb2
clr
push 2
push 1
cmp
jg lb3
push 1
quit
:lb3
push 2
add
cmp
jl lb4
push 1
quit
:lb4
clr
push 0

quit
