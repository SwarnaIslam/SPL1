.data
	num1: .word 2
	array: .space 7
	num2: .word 4
.text


	loading:
	lw $s0 num1
	lw $s1 num2

	adding:
	addi $sp $sp -8

	storing:
	sw $s0 0($sp)
	sw $s1 4($sp)

	li $v0 1
	move $a0 $s0
	syscall

	



		