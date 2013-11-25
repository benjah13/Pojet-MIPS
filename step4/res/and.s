## Test de and
 
.text
and $8, $8, $9 		# $8 & $9 dans $8
and $8, $24, $12	# $8 & $24 dans $12
nop

.bss
Tab: 
.space 12 			# réserve 12 octets en mémoire, 
					# par exemple pour stocker un tableau de 3 entiers
 
## The end
