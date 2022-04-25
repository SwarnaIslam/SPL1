.data

.text
lbl1:
li $t0 1
li $t1 12
blt $t0 $t1 adding


adding:
add $a0 $zero $t0

li $v0 1
syscall

exit: