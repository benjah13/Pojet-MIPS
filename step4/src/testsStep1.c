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
#include "structure.h"
#include "libelf.h" 
#include "shellStep3.h"
#include "notify.h" 
#include "fonctions.h" 
#include "constantes.h" 
#include "fonctionsStep1.h" 
#include "testsStep1.h" 
#include "fonctionsStep2.h" 
#include "elfimport.h"
#include "cmdSearch.h"
#include "execution.h"
#include "man.h"

/* FONCTION TEST REGISTRE */
int test_registre(char* input){

	if(input==NULL||input[1]=='\0'){return -2;}  

	else if(input[0]!='$'){return -1;}

	
	 
	/* AUTRES REGISTRES */
	
	else if((input[2]=='2'&&input[3]=='8'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='g'&& input[3]=='p'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='8'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='g'&&input[2]=='p'&&(input[3]=='\0'||input[3]=='\n'))){return 28;}

	else if((input[2]=='2'&&input[3]=='9'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='p'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='9'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='p'&&(input[3]=='\0'||input[3]=='\n'))){return 29;}

	else if((input[2]=='3'&&input[3]=='0'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='f'&& input[3]=='p'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='3'&&input[2]=='0'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='f'&&input[2]=='p'&&(input[3]=='\0'||input[3]=='\n'))){return 30;}

	else if((input[2]=='3'&&input[3]=='1'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='r'&& input[3]=='a'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='3'&&input[2]=='1'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='r'&&input[2]=='a'&&(input[3]=='\0'||input[3]=='\n'))){return 31;}

	else if((input[2]=='3'&&input[3]=='2'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='P'&& input[3]=='C'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='3'&&input[2]=='2'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='p'&&input[2]=='c'&&(input[3]=='\0'||input[3]=='\n'))){return 32;}

	else if((input[2]=='3'&&input[3]=='3'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='H'&& input[3]=='I'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='3'&&input[2]=='3'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='H'&&input[2]=='I'&&(input[3]=='\0'||input[3]=='\n'))){return 33;}

	else if((input[2]=='3'&&input[3]=='4'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='L'&& input[3]=='0'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='3'&&input[2]=='4'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='L'&&input[2]=='0'&&(input[3]=='\0'||input[3]=='\n'))){return 34;}
 
	/* REGISTRES $k1  $k2 */

	else if ((input[2]=='2'&&input[3]=='6'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='k'&& input[3]=='0'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='6'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='k'&&input[2]=='0'&&(input[3]=='\0'||input[3]=='\n'))){return 26;}

	else if((input[2]=='2'&&input[3]=='7'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='k'&& input[3]=='1'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='7'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='k'&&input[2]=='1'&&(input[3]=='\0'||input[3]=='\n'))){return 27;}
	
	/* REGISTRES $t8  $t9 */

	else if((input[2]=='2'&&input[3]=='4'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&& input[3]=='8'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='4'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='t'&&input[2]=='8'&&(input[3]=='\0'||input[3]=='\n'))){return 24;}

	else if((input[2]=='2'&&input[3]=='5'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&& input[3]=='9'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='5'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='t'&&input[2]=='9'&&(input[3]=='\0'||input[3]=='\n'))){return 25;}
	
	/* REGISTRES $s0 ... $s7 */
	
	else if((input[2]=='1'&&input[3]=='6'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='0'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2]=='6'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='0'&&(input[3]=='\0'||input[3]=='\n'))){return 16;}
	
	else if((input[2]=='1'&&input[3]=='7'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='1'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2]=='7'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='1'&&(input[3]=='\0'||input[3]=='\n'))){return 17;}

	else if((input[2]=='1'&&input[3]=='8'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='2'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2]=='8'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='2'&&(input[3]=='\0'||input[3]=='\n'))){return 18;}

	else if((input[2]=='1'&&input[3]=='9'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='3'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2]=='9'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='3'&&(input[3]=='\0'||input[3]=='\n'))){return 19;}

	else if((input[2]=='2'&&input[3]=='0'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='4'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='0'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='4'&&(input[3]=='\0'||input[3]=='\n'))){return 20;}

	else if((input[2]=='2'&&input[3]=='1'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='5'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='1'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='5'&&(input[3]=='\0'||input[3]=='\n'))){return 21;}

	else if((input[2]=='2'&&input[3]=='2'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='6'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='2'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='6'&&(input[3]=='\0'||input[3]=='\n'))){return 22;}

	else if((input[2]=='2'&&input[3]=='3'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='s'&& input[3]=='7'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='2'&&input[2]=='3'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='s'&&input[2]=='7'&&(input[3]=='\0'||input[3]=='\n'))){return 23;}
	
	
	/* REGISTRES $t0 ... $t7 */

	else if((input[2]=='8'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='8'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='t'&& input[2]=='0'&&(input[3]=='\0'||input[3]=='\n')) ||  (input[2]=='t'&& input[3]=='0'&&(input[4]=='\0'||input[4]=='\n'))){return 8;}

	else if((input[2]=='9'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='9'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='t'&& input[2]=='1'&&(input[3]=='\0'||input[3]=='\n'))|| (input[2]=='t'&& input[3]=='1'&&(input[4]=='\0'||input[4]=='\n'))){return 9;}
	
	else if((input[2]=='1'&& input[3] == '0' &&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='1'&&input[2]=='0' &&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='t'&&input[2]=='2'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&&input[3]=='2'&&(input[4]=='\0'||input[4]=='\n'))){return 10;}
	
	else if((input[2]=='1'&&input[3]=='1'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='1' && input[2] == '1'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='t'&&input[2]=='3'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='t'&& input[3]=='3'&&(input[4]=='\0'||input[4]=='\n'))){return 11;}

	else if((input[2]=='1'&&input[3]=='2'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='1' &&input[2]=='2'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='t'&& input[2]=='4'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&&input[3]=='4'&&(input[4]=='\0'||input[4]=='\n'))){return 12;}

	else if((input[2]=='1'&&input[3]=='3'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&& input[3]=='5'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2]=='3'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='t'&&input[2]=='5'&&(input[3]=='\0'||input[3]=='\n'))){return 13;}

	else if((input[2]=='1'&&input[3]=='4'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&& input[3]=='6'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2]=='4'&&(input[3]=='\0'||input[3]=='\n'))|| (input[1]=='t'&&input[2]=='6'&&(input[3]=='\0'||input[3]=='\n'))){return 14;}

	else if((input[2]=='1'&&input[3]=='5'&&(input[3]=='\0'||input[3]=='\n'))||(input[2]=='t'&& input[3]=='7'&&(input[4]=='\0'||input[4]=='\n'))||(input[1]=='1'&&input[2] == '5'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='t'&& input[2]=='7'&&(input[3]=='\0'||input[3]=='\n'))){return 15;}
	
	
	
	 /* REGISTRES $aO ... $a3 */

	else if((input[2]=='4'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='4'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='a'&& input[2]=='0'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='a'&& input[3]=='0'&&(input[4]=='\0'||input[4]=='\n'))){return 4;}
	
	else if((input[2]=='5'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='5'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='a'&& input[2]=='1'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='a'&& input[3]=='1'&&(input[4]=='\0'||input[4]=='\n'))){return 5;}

	else if((input[2]=='6'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='6'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='a'&& input[2]=='2'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='a'&& input[3]=='2'&&(input[4]=='\0'||input[4]=='\n'))){return 6;}

	else if((input[2]=='7'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='7' && ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='a'&& input[2]=='3'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='a'&& input[3]=='3'&&(input[4]=='\0'||input[4]=='\n'))){return 7;}

	/* REGISTRES $vO $v1 */

	else if((input[2]=='2'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='2'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='v'&& input[2]=='0'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='v'&& input[3]=='0'&&(input[4]=='\0'||input[4]=='\n'))){return 2;}

	else if((input[2]=='3'&&(input[3]=='\0'||input[3]=='\n'))||(input[1]=='3'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='v'&& input[2]=='1'&&(input[3]=='\0'||input[3]=='\n')) || (input[2]=='v'&& input[3]=='1'&&(input[4]=='\0'||input[4]=='\n'))){return 3;}

	/* Registres 1 et 2 */
	
	else if((input[2]=='0'&&(input[3]=='\0'||input[3]=='\n')) || (input[1]=='0'&& ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='z'&& input[2]=='e'&& input[3]=='r'&& input[4]=='o' &&(input[5]=='\0'||input[5]=='\n')) || (input[2]=='z'&& input[3]=='e'&& input[4]=='r'&& input[5]=='o' &&(input[6]=='\0'||input[6]=='\n'))){return 0;}

	else if((input[2]=='1'&&(input[3]=='\0'||input[3]=='\n')) || ( input[1]=='1' && ( input[2]=='\0' || input[2]=='\n'))|| (input[1]=='a'&& input[2]=='t'&&(input[3]=='\0'||input[3]=='\n'))|| (input[2]=='a'&& input[3]=='t'&&(input[4]=='\0'||input[4]=='\n'))){return 1;}
	 
	
	else {return -3;}

	return -4; /* tout les cas ont été traités */ 
}

/* FONCTION TEST MEMOIRE */
int test_memoire(mips* arch, unsigned int adresse, unsigned int* addr_in_block)
{	
	if(adresse<arch->segment[BSS].startAddress+arch->segment[BSS].size && adresse>=arch->segment[BSS].startAddress)
	{
		*addr_in_block=adresse-arch->segment[BSS].startAddress;
		return BSS;
	}

	if(adresse<arch->segment[TEXT].startAddress+arch->segment[TEXT].size && adresse>=arch->segment[TEXT].startAddress)
	{
		*addr_in_block=adresse-arch->segment[TEXT].startAddress;
		return TEXT;
	}	
	
	if(adresse<arch->segment[DATA].startAddress+arch->segment[DATA].size && adresse>=arch->segment[DATA].startAddress)
	{
		*addr_in_block=adresse-arch->segment[DATA].startAddress;
		return DATA;
	}

	if(adresse<arch->segment[STACK].startAddress+arch->segment[STACK].size && adresse>=arch->segment[STACK].startAddress)
	{
		*addr_in_block=adresse-arch->segment[STACK].startAddress;
		return STACK;
	}

	else
	{
		return -1;
	}
}

/* FONCTION TEST VALEUR */
int test_valeur(unsigned int val)
{
	if(val>255)
	{
		return -1;
	}

	else return 1;
}
