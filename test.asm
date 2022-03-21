.data
label: .word 9
#text: .asciiz "text"
.text
li $s0 214748364
li $s1 4
mult $s0 $s1
mflo $s2

li $v0 1
move $a0 $s2
syscall

mfhi $s3

li $v0 1
move $a0 $s3
syscall