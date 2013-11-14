## Test de add
 
.text
beq $t0, $t1, 8		# offset de 8 si $8 = $9
beq $t0, $t9, 12	# offset de 12 si $8 = $24
nop

.bss
Tab: 
.space 12 			# réserve 12 octets en mémoire, 
					# par exemple pour stocker un tableau de 3 entiers
 
## The end
