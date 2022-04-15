.data
num1: .space 10
num2: .word -9 2
num3: .space 3
num4: .word 1 2 3 4

.text
main:
li $t0 -10
abs $a0 $t0
li $v0 1
syscall
li $t0 -214748364
li $t1 21474836
sub $t2 $t0 $t1
