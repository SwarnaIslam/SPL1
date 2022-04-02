.data
num: .word -9
.text
main:
li $t0 -10

abs $a0 $t0

li $v0 1
syscall

li $t0 -2147483648
li $t1 2147483647

sub $t2 $t0 $t1
