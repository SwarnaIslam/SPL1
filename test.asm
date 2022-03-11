.data
test1: .word  21
.text
test2:  
li $v0 1
li $a0 20
syscall

li $v0 5
syscall

li $v0 34
syscall