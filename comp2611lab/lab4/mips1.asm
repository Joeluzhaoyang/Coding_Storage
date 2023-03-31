.data
X: .word 2 18 3 
Y: .word 20 4 
.text 
.globl __start 
__start: 
addi $t0, $zero, 1
addi $t1, $t0, -2