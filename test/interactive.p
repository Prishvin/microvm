#test define, array, variable
$define _element 101
var v1
var arr 10
push _element
push 0
atom arr
pop
pop
push 200
push 1
atom arr
pop
pop
push _element
push 2
atom arr
pop
pop
push 1 
tomm v1
pop
push 0
afrom arr 
frmm v1
sub
push 2
afrom arr 
frmm v1
sub
assert
push 5
call square
push 25
assert
pop
pop
push 5
call qube
push 125
assert
push 10
cmp
call square
push 100
cmp 
call t1000
push 5
cmp
call t2000
push 0
push 1000
push 1000
cmp
je finish
push 65356
:finish
push 0
quit
:square
dup
mul
ret
:qube
dup
dup
mul
mul
ret
:t1000
push 1000
ret
:t2000
push 2000
ret
