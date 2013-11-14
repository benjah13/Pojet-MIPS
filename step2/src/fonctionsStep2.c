#include <stdlib.h>
#include <stdint.h> 
#include <stdio.h> 
#include <string.h> 
#include <libelf.h> 
#include "libelf.h" 
#include <math.h>

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

/* Fonction qui tronque une valeur sur 4 octets */ 
unsigned int getbits(unsigned int val, unsigned int start, unsigned int stop){

	unsigned int test=0xFFFFFFFF; 
	unsigned int shorten;

	if(stop>31){ 
		fprintf(stdout,"Stop too big\n"); 
		return 2; 
		}

	else if(start>stop){
		fprintf(stdout,"Start upper than stop\n"); 
		return 2; 
		} 
	else { 
		test=(test>>start)<<start; 
		test=(test<<(31-stop))>>(31-stop); 
		shorten=val&test; 
		} 
	
	shorten=shorten>>start; 
	return shorten; 
}


/****************************************/ 
/***** FONCTIONS DISPLAY ASSEMBLER ******/ 
/***************************************/

int parse_and_execute_cmd_da(char* input, mips* arch){
	
	INFO_MSG("Entering the function parse_and_execute_cmd_da");

	/* déclaration des variables */ 
	int i=1; 
	char *pch, *pch2; 
	unsigned int arg1,arg2; 
	char* separators=" "; 
	
	/* On teste d'abord la presence de plusieurs arguments */ 
	pch2=strtok(input,separators); 

	if(pch2==NULL){ 
		fprintf(stdout,"Too few arguments. Format da 0xaddr:nb_instr\n"); 
		return 2; 
		} 
	
	pch2=strtok(NULL,separators); 
	if (pch2!=NULL) { 
		fprintf(stdout,"DA function only takes one argument! Format da 0xaddr:nb_instr\n");
		return 2;
		}

	/* On réinitialise le pointeur au debut de la chaine*/ 
	pch=strtok(input,separators);

	/* VERIFICATION DE LA PRESENCE DES 2 ARGUMENTS SEPARES PAR ":" */
	if(strchr(pch,':')==NULL){ 
		fprintf(stdout,"Invalid argument: format da 0xaddr:nb_instr\n"); 			
		return 2;
		}

	pch=strtok(pch,":"); 

	/* si l'adresse commence par '0x' on décale le pointeur de 2 caractères */ 
	if(pch[0]=='0' && pch[1]=='x'){pch=pch+2;} 
	else{fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n"); return 2;}

	/* test longueur de l'argument 1 */ 
	if (strlen(pch)>8) { 
		fprintf(stdout,"Invalid param : parameter should be between 0xOOOOOOOO and 0xffffffff\n"); 
		return 2;
		} 

	/* test base 16 */ 
	while(i!=strlen(pch)){ 
		if(!isxdigit(pch[i])){ 
			fprintf(stdout,"Invalid param : hexadecimal number awaited in '%s'\n", pch);
			return 2;
			} 
		i++;
		} 
	
	arg1=(unsigned int)strtol(pch,NULL,16);
	pch=strtok(NULL,":"); 
	i=1;

	/* test argument 2 base 10 */
	while(pch[i]!='\0' && pch[i]!='\n'){ 
		
		if(!isdigit(pch[i])){ 
			fprintf(stdout,"Invalid param : decimal number awaited in '%s'\n", pch); 
			return 2;
			} 
		i++; 
		} 
	
	arg2=(unsigned int)strtol(pch,NULL,10); 
	
	if(arg2>1000) { 
		fprintf(stdout,"Invalid param : maximum number of instructions to display is 1000\n"); 
		return 2; 
		} 

	pch=strtok(NULL,separators); 

	if (pch!=NULL) { 
		fprintf(stdout,"DA function only takes one argument!\n"); 
		return 2; 
		}

return execute_cmd_da(arg1,arg2,arch); 

}

int execute_cmd_da(unsigned int addr, unsigned int nbr_instr, mips* arch){
 
	INFO_MSG("Entering the function execute_cmd_da");
	
	/* recalage des adresses */	
	addr=addr-addr%4;

	/* Déclaration des variables */
	BYTE* bits;
	unsigned int i=0;
	unsigned int nb_int=0;
	

	/* Boucle sur le nb d'instructions à désassembler */
	for(i=0;i<nbr_instr;i++){ 

		/* Chargement d'une instruction */
		bits=&(arch->segment[TEXT].data[arch->segment[TEXT].startAddress+addr])+4*i;
		//fprintf(stdout,"String to disassemble : %02x %02x %02x %02x\n",bits[0],bits[1],bits[2],bits[3]);

		/* Inversion little endian->big endian */
		char str[8];
		sprintf(str,"%02x",bits[0]);
		sprintf(str+2,"%02x",bits[1]); 
		sprintf(str+4,"%02x",bits[2]); 
		sprintf(str+6,"%02x",bits[3]);

		//fprintf(stdout,"String to disassemble base 16 : %s\n",str); 

		/* nb_int = string d'instruction */
		nb_int=strtol(str,NULL,16);

		//fprintf(stdout,"String to disassemble base 10 : %ld\n",nb_int);
		
		unsigned int j=0;

		/* Affichage de la chaîne binaire */
		
		unsigned int binaryNumber[32];
		memset(binaryNumber,0,32*sizeof(int));
		
		unsigned int quotient=nb_int;

		while(quotient!=0){

			binaryNumber[31-j]=quotient%2;
			quotient=quotient/2;
			j++;
			}

		
		/* fprintf(stdout,"Binary string to work on : "); 

		for(j=0;j<32;j++){
			fprintf(stdout,"%d",binaryNumber[j]);
			}

		fprintf(stdout,"\n"); */

		/* Test sur l'opcode */
		unsigned int opcode=0;
		opcode=getbits(nb_int,26,31);

		char* instr=malloc(7*sizeof(char));

		unsigned int rs=0,rt=0,rd=0,sa=0,function=0,target=0;
		unsigned int attribut=0;
		
		rs=getbits(nb_int,21,25);
		rt=getbits(nb_int,16,20);

		if(opcode==0){
			/* Variables correspondant à un type R */
			rd=getbits(nb_int,11,15);
			sa=getbits(nb_int,6,10);
			function=getbits(nb_int,0,5);
			/* Recherche de la commande de type R */
			instr=cmdSearch("R",function);
			}

		else{
			/* Variables correspondant à un type I ou J */
			attribut=getbits(nb_int,0,15);
			target=getbits(nb_int,0,25);
			/* Recherche de la commande de type I ou J */
			instr=cmdSearch("IJ",opcode);
			}
		
		/* Si l'opcode n'est pas connu */
		if(instr==NULL){
			fprintf(stdout,"%08x:	",addr+4*i);
			fprintf(stdout,"Unknown instruction\n");}
		else{
		/* Ouverture du fichier ./dictionnary/cmd.desc */
		char* filename=malloc(30*sizeof(char));

		sprintf(filename,"%s%s%s","./dictionnary/",instr,".desc");

		FILE* f=fopen(filename,"r");

		if(strcmp("SLL",instr)==0 && strcmp(arch->reg[rd].mnemo,"zero")==0 && strcmp(arch->reg[rt].mnemo,"zero")==0 && sa==0){
			fprintf(stdout,"%08x:	",addr+4*i);
			fprintf(stdout,"NOP");
			}

		else{
		/* Affichage de la commande */
		fprintf(stdout,"%08x:	%s	",addr+4*i,instr);

		do{

		char* arg=malloc(15*sizeof(char));
		fscanf(f,"%s",arg);

		/* écriture des instructions selon le format du .desc */
		if(strcmp("rs",arg)==0){fprintf(stdout,"$%s ",arch->reg[rs].mnemo);}
		else if(strcmp("rs,",arg)==0){fprintf(stdout,"$%s, ",arch->reg[rs].mnemo);}
		else if(strcmp("rt",arg)==0){fprintf(stdout,"$%s ",arch->reg[rt].mnemo);}
		else if(strcmp("rt,",arg)==0){fprintf(stdout,"$%s, ",arch->reg[rt].mnemo);}
		else if(strcmp("rd",arg)==0){fprintf(stdout,"$%s ",arch->reg[rd].mnemo);}
		else if(strcmp("rd,",arg)==0){fprintf(stdout,"$%s, ",arch->reg[rd].mnemo);}
		else if(strcmp("sa",arg)==0){fprintf(stdout,"%d",sa);}
		else if(strcmp("offset",arg)==0){fprintf(stdout,"%d",attribut);}
		else if(strcmp("offset(base)",arg)==0){fprintf(stdout,"%d(%d)",attribut,rs);}
		else if(strcmp("immediate",arg)==0){fprintf(stdout,"%d",(int16_t)attribut);}
		else if(strcmp("target",arg)==0){fprintf(stdout,"%d",target);}
		}

		while(!feof(f));
		}

		fprintf(stdout,"\n");

		fclose(f);
		free(instr);
		free(filename);

		}
		}
	
	return CMD_OK_RETURN_VALUE;

}

/**************************************/ 
/***** FONCTIONS LOAD PROGRAM *********/ 
/*************************************/

/* fonction parse_and_execute_cmd_lp */

int parse_and_execute_cmd_lp(char* input, mips* arch){

	INFO_MSG("Entering the function parse_and_execute_cmd_lp");

	FILE* program=NULL;
	char* pch; 
	char* separators=" ";
	pch=strtok(input,separators); 

	/* Test de la presence d'arguments*/ 
	if(pch==NULL){ 
		fprintf(stdout,"Too few arguments\n");
		return 2;
		}

	/* test si l'extension ELF est presente */ 
	if(strstr(pch,".o")==NULL && strstr(pch,".O")==NULL){ 
		fprintf(stdout,"Unknown file format. File should be an .o file\n");
		return 2;
		} 

	
	/* on ouvre le fichier */ 
		char* elfname=malloc((7+strlen(pch))*sizeof(char));
		elfname=elfname+1;
		sprintf(elfname,"%s%s","./res/",pch);	

		program=fopen(elfname,"r");
	
	if(program==NULL){
		fprintf(stdout,"%s doesn't exist or can't be loaded\n",elfname); 			
		return 2;
		}

	/* on regarde s'il y'a plus d'arguments */  
	pch=strtok(NULL,separators); 

	if (pch!=NULL){ 
		fprintf(stdout,"LP function only takes one argument!\n");
		return 2;
		}

	return execute_cmd_lp(program,elfname,arch);

}

/* fonction execute_cmd_lp */

int execute_cmd_lp(FILE* program , char *nom_fichier ,mips *arch){

	INFO_MSG("Entering the function execute_cmd_lp");
	
	mipsloader(nom_fichier, &arch->segment[TEXT], &arch->segment[DATA], &arch->segment[BSS]); 

	return CMD_OK_RETURN_VALUE;

}
