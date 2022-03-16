.data
label: .word 9
#text: .asciiz "text"
.text
li $s0 -2147483647
li $v0 -2
move $a0 $v0


add $t0 $s0 $a0
addi $s0 $zero 1

