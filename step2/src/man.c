#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libelf.h>
#include "libelf.h"

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>


/* macros de DEBUG_MSG fournies , etc */
#include "global.h"
#include "mipself.h"
#include "notify.h"
#include "structure.h"
#include "constantes.h"
#include "fonctions.h"
#include "fonctionsStep1.h"
#include "testsStep1.h"
#include "fonctionsStep2.h"
#include "elfimport.h"
#include "man.h"

int man(void)
{
  fprintf(stdout, "Manuel des commandes du Simulateur Mips\n\n");
  fprintf(stdout,"- Load Program :      ( format : 'lp mon_programme.o' ) ouvre le programme mon_programme.o se trouvant dans le repertoire res et met les instructions et les données dans la mémoire de notre simulateur\n");
  fprintf(stdout, "- Display Register:   ( format 'dr $i' ) affiche la valeur contenu dans le registre $i \n\t              ( format 'dr' ) affiche la valeur de tout les registres\n");
  fprintf(stdout, "- Load Register:      ( format 'lr $i 0xval' ) ecrit la valeur val héxadécimal edans le registre $i\n");
  fprintf(stdout, "- Display Memory:     ( format 'dm 0xAddr' ) affiche la valeur contenu dans l'adresse héxadécimal Addr\n\t              ( format 'dm 0xAddr:nboct' ) affiche les valeurs dans la mémoire des nboct octets suivant Addr \n\t              ( format 'dm 0xAddr~0xAddr2' ) affiche la zone mémoire entre Addr et Addr2 \n");
  fprintf(stdout, "- Load Memory:        ( format 'lm 0xAddr 0xVal' ) écrit la valeur Val dans l'addres Addr.\n");
  fprintf(stdout,"- Display Assembler:  ( format 'da 0xAddr:nb_inst' ) affiche les nb_instr instructions de la mémoire désassemblée a partir de l'adresse Addr \n");

  return 0;
}