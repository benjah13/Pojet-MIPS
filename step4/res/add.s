## Test de add
 
.text
add $8, $8, $9 		# ajoute 17 au registre 8
add $8, $24, $12	# ajoute 18 au registre 8
nop

.bss
Tab: 
.space 12 			# réserve 12 octets en mémoire, 
					# par exemple pour stocker un tableau de 3 entiers
 
## The end
