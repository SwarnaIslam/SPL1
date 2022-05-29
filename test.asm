.data
	
	num1: .word 2

	array1: .space 7

	num2 : .word 3
.text

	main:

	li $v0 1
	lw $a0 num1
	syscall

	main2:

	main3:
		