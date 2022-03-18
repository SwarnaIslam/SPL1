.data
label: .word 9
#text: .asciiz "text"
.text
li $s0 2147483647
li $s1 3
mul $s2 $s0 $s1
li $v0 1
move $a0 $s2
syscall