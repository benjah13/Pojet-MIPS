## Test de div
 
.text
div $t0, $t9		# divise $8 par $24
div $t0, $t0 		# divise $8 par $8
nop

.bss
Tab: 
.space 12 			# réserve 12 octets en mémoire, 
					# par exemple pour stocker un tableau de 3 entiers
 
## The end
