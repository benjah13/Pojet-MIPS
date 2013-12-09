## Test de add
 
.text
addi $8, $8, 0x12
add $8, $9
nop

.bss
Tab: 
.space 12 			# réserve 12 octets en mémoire, 
					# par exemple pour stocker un tableau de 3 entiers
 
## The end
