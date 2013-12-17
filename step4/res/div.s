.set noreorder

addi $t1,$zero,2
addi $t2,$zero,4
mult $t2,$t1
div $t2,$t1
mfhi $t3
mflo $t4
lw $t5,0x28($zero) # recuperer le code de MFHI
sw $zero,0($zero) #ecrase la premiere instruction avec un NOP
