.set noreorder
.text

ADDI $7,$zero,44444  # met 44444 dans le registre $7
ADDI $5,$zero,12     # met 12 dans le registre $5
ADD $5,$7	     # somme les registres $5 et $7 dans $5
JAL reloc            # Appel à la procédure "reloc"  
NOP                  # delay slot 
B end                # On revient ici après le "write" branchement vers la fin 
NOP

reloc:
sw $7,Z              # écrit le contenu de $7 à l'adresse de Z
lw $6,X		     # écrit le contenu de l'adresse X dans $6
JR $31               # fin de la procédure, retour à l'appelant
NOP

end:
syscall              # la fin consiste en un appel explicite à syscall pour sortir du 			     # programme


.data 
X: .byte 0xF5        # un octet initialisé à F5 à l'adresse X
X1:.word 0	     # un octet parasite pour vérifier que la reloc marche...
Y: .word Z           # un mot de 32 bits initialisé à la valeur de Z
Z: .word 0           # un mot de 32 bits initialisé à zéro à l'adresse Z
