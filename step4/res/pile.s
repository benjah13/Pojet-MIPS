.set noreorder
.text

main:
addi $v0,$v0,10		# le paramètre passé à la fonction toto sera 10

addi $sp, $sp, -4 	# Stack Pointer decrementé : sp = sp-4
sw $v0, 0x0($sp) 	# on stocke le paramètre v0 sur la pile pour le jal toto
jal toto 		# appel de la fonction
lw $v0, 0x0($sp) 	# recuperation du parametre v0
addi $sp,$sp,4		# Increment du SP
nop 			# delay slot etc.. suite du main
syscall

toto:
addi $v1,$v1,100
addi $sp, $sp, -4 	# Creation d'une variable locale
sw $v1, 0x0($sp)	# Initialisation de la variable locale
addi $sp,$sp,4 		# destruction de la variable locale
jr $ra
nop
