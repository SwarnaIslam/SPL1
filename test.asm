.data
num: .word -9 
.text
main:
li $t0 -9

move $a0 $t0
abs $a0 $a0

li $v0 1
syscall
lalala:

lulululu:
li $t0 -1
li $t1 2147483647

sub $t2 $t0 $t1
