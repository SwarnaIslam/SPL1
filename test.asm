.data

.text

li $s0 7
sll $t0 $s0 31
li $s1 29

sllv $t0 $s0 $s1
li $v0 1
move $a0 $t0
syscall