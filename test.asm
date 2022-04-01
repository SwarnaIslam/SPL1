.data
	#nl: .asciiz"\n"
	label: .word 1
	label1: .word 2
.text
label2:
li $s0 -10929
addi $t0 $s0 -248487

not $t1 $t0

li $v0 1
move $a0 $t1
syscall

and $t2 $t1 $s0

li $v0 1
move $a0 $t2
syscall

not $t1 $s0

li $v0 1
move $a0 $t1
syscall

and $t3 $t1 $t0

li $v0 1
move $a0 $t3
syscall

or $t1 $t2 $t3

li $v0 1
move $a0 $t1
syscall

xor $t1 $t0 $s0

li $v0 1
move $a0 $t1
syscall

