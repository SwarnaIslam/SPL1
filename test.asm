.data
num1: .space 8
num2: .word 12 3 4
num3: .space 5
num4: .word 1
.text
lbl1:
li $t1 4
la $t0 num2
lw $a0 num2($t1)
li $v0 1
syscall

exit:
