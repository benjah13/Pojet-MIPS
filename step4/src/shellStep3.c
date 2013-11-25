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


void Initialisation(unsigned int addr,Liste_Bp* liste){

  unsigned int address;
  address=addr-addr%4;
  if (address!=addr)
  {
    fprintf(stdout,"L'argument %d a été modifié en %d pour etre le debut d'une instruction\n",addr,address);
  }
	Breakpoint *element=malloc(sizeof(*element));
  
	if(liste==NULL||element==NULL){

		fprintf(stdout,"Impossible d'initialiser la liste \n");
		exit(EXIT_FAILURE);
		}
  
	element->addr = address ;
	element->suivant = NULL;
	liste->premier = element;
	liste->dernier = element;
	liste->nb_bp=1;
	
	fprintf(stdout,"Breakpoint set at address 0x%x\n",address);

  
}	


int SetBP(Liste_Bp *liste,unsigned int addr1){

  
  unsigned int addr;
  addr=addr1-addr1%4;
  if (addr1!=addr)
  {
    fprintf(stdout,"L'argument %d a été modifié en %d pour etre le debut d'une instruction\n",addr1,addr);
  }
	Breakpoint *nouveau = malloc(sizeof(*nouveau));
	Breakpoint *dernier = malloc(sizeof(*dernier));
	Breakpoint *actuel = malloc(sizeof(*actuel));

	if(liste==NULL||nouveau==NULL || dernier==NULL ){

	fprintf(stdout,"Impossible d'ajouter un breakpoint a la liste \n");
	exit(EXIT_FAILURE);
	}
	
	actuel=liste->premier;
	while(actuel!=NULL)
	{
	  if (actuel->addr==addr)
	  {
	    fprintf(stdout,"This BreakPoint already exists\n");
	    return 1;
	  }
	  actuel=actuel->suivant;
	}
 
	(liste->dernier)->suivant=nouveau;

 	nouveau->addr=addr;  
	nouveau->suivant=NULL;
    
	liste->dernier=nouveau;
	(liste->nb_bp)++;

	fprintf(stdout,"Breakpoint set at address 0x%x\n",addr);

	return 0;
	}

/* parse_and_execute_cmd_run */
int parse_and_execute_cmd_run(char* input, mips* arch,Liste_Bp* liste){

	INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_run");

	/* déclaration des variables */ 	
	int i=0;
	char* pch;
	char* separators=" ";
	unsigned int arg1=0;
	unsigned int addr_in_block;
	
	pch=strtok(input," ");
	/* Test de la presence d'arguments*/
	if(pch==NULL){
		return execute_cmd_run(-1,arch,liste);
		}
	
	else if(pch[0]=='0' && pch[1]=='x'){
		pch=pch+2;
		}	
	else{
		fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n");
		return 2;
		}
	
	/* parsing de l'adresse */

	/* test longueur de l'argument 1 */
	if (strlen(pch)>8) { 
		fprintf(stdout,"Argument too long\n");
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
	/* si l'adresse est bien en héxadécimal */
	i=0;
	arg1=(unsigned int)strtol(pch,NULL,16);
	if(test_memoire(arch,arg1,&addr_in_block)!=TEXT){
		fprintf(stdout,"Warning : The address is not in the TEXT section!\n");
		return 2;
		}
	pch=strtok(NULL,separators);

	if(pch!=NULL){
		fprintf(stdout,"Run only takes one argument!\n");
		return 2;
		}
	
	return execute_cmd_run(arg1,arch,liste);
	
	}

/* execute_cmd_run */
int execute_cmd_run(unsigned int addr, mips* arch, Liste_Bp* liste){ 
 
	INFO_MSG("Entering the function Execute_cmd_run");
	int instruction_int=0;
	void (*executor[128])(int,mips*);

	/* initialisation d'un booléen ==1 si procedure ==0 sinon */
	int procedure=0;

	/* remplissage du tableau de fonctions */
	init_functionTab(arch,executor);
	
	/* s'il n'y a pas de breakpoint */
	if (addr!=-1){
		arch->reg[32].val=addr;
		}

	while(arch->reg[32].val<(arch->segment[TEXT].startAddress+arch->segment[TEXT].size)){

		/* Récupération de l'instruction à l'adresse addr */
		instruction_int=getword(arch->reg[32].val,arch);

		/* Recherche de la commande à exécuter par l'opcode ou le function */
		int code=0;

		/* initialisation à typeR opcode=0 + shift dans le tableau des fonctions */
		code=getbits(instruction_int,26,31)+64;
		
		/* si non typeR alors typeIJ récupération de function */
		if(code==64){
			int function=0;
			function=getbits(instruction_int,0,5);
			code=function;
			}
			
		/* Exécution de la commande */
		executor[code](instruction_int,arch);
		
		/* s'il y a une procédure : cad appel de jal */
		if (code==67){
				procedure=1;

				do {
	
				/* Récupération de l'instruction à l'adresse addr */		
				instruction_int=getword(arch->reg[32].val,arch);

				/* Recherche de la commande à exécuter par l'opcode ou le function */
				code=0;
	
				/* initialisation à typeR opcode=0 + shift dans le tableau des fonctions */
				code=getbits(instruction_int,26,31)+64;
				    
				/* si non typeR alors typeIJ récupération de function */
				if(code==64){
					int function=0;
					function=getbits(instruction_int,0,5);
					code=function;
					}
					    
				/* Exécution de la commande */
				executor[code](instruction_int,arch);

				/* test si retour au jal+4 */
				if(arch->reg[32].val==arch->reg[31].val){procedure=0;}
			  
				/* Incrémentation du PC */
				if(procedure){
					arch->reg[32].val=arch->reg[32].val+4;
					}

				/* test breakpoint */
				if(isBP(arch->reg[32].val,liste)==1){
					return CMD_OK_RETURN_VALUE;
					}
			
				}
				while(procedure);

			}
		
		/* Incrémentation du PC */
		if(procedure==0 && code!=8 && code!=66){arch->reg[32].val=arch->reg[32].val+4;}
		
		/* test breakpoint */
		if(isBP(arch->reg[32].val,liste)==1){
				return CMD_OK_RETURN_VALUE;
				}

		/* reinitialisation de procedure */
		procedure=0;

		}
		
	return CMD_OK_RETURN_VALUE;

	}


/* Parse_and_execute_cmd_bp */
int parse_and_execute_cmd_bp(char* input, mips* arch ,Liste_Bp* liste){

	INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_bp");

	/* déclaration des variables */ 	
	int i=0;
	char* pch;
	char* separators=" ";
	unsigned int arg1=0;
	unsigned int addr_in_block;
	
	pch=strtok(input," ");
	/* Test de la presence d'arguments*/
	if(pch==NULL){
		fprintf(stdout,"Too Few Argument!\n");
		return 2;
		}
	
	else if(pch[0]=='0' && pch[1]=='x'){
		pch=pch+2;
		}	
	else{
		fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n");
		return 2;
		}
	
	/* parsing de l'adresse */
	
	/* test longueur de l'argument 1 */
	if (strlen(pch)>8) { 
		fprintf(stdout,"Argument too long\n");
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
	/* si l'adresse est bien en héxadécimal */
	i=0;
	arg1=(unsigned int)strtol(pch,NULL,16);
	pch=strtok(NULL,separators);

	if(pch!=NULL){
		fprintf(stdout,"Bp only takes one argument!\n");
		return 2;
		}
	
	if(test_memoire(arch,arg1,&addr_in_block)<0){
		fprintf(stdout,"Warning : The address is not allocated for the simulator!\n");
		return 2;
		}

	return execute_cmd_bp(arg1,arch,liste); 
  
	}

/* Execute_cmd_bp */
int execute_cmd_bp(unsigned int addr, mips* arch, Liste_Bp* liste){

	if(liste->nb_bp==0){
		Initialisation(addr,liste);
		}
	else if(SetBP(liste,addr)==1){
		return 2;
		}
		
	return CMD_OK_RETURN_VALUE;
	
	}

/* Eceute_cmd_db */
int execute_cmd_db(char* input, Liste_Bp* liste){

	char* pch;
	pch=strtok(input," ");
	
	if(pch!=NULL){
		fprintf(stdout,"Too Much argument\n");
		return 2;
		}
  
	int i=1;
	Breakpoint *actuel = malloc(sizeof(*actuel));

	if(actuel==NULL){
		fprintf(stdout,"Erreur Fatal, problème d'allocation\n");
		exit(EXIT_FAILURE);
  		}

	actuel=liste->premier;
  
    	while(actuel!=NULL){
		fprintf(stdout,"Breakpoint %d : 0x%x \n",i,actuel->addr);
		actuel=actuel->suivant;
		i++;
		}

	return CMD_OK_RETURN_VALUE;

	}


/* Parse_adn_execute_cmd_step */
int parse_and_execute_cmd_step(char* input ,mips* arch,Liste_Bp* liste){

	INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_step");

	char* pch;
	pch=strtok(input," ");
	
	if(pch!=NULL){
		fprintf(stdout,"Too Much argument\n");
		return 2;
		}
		
		
	if(arch->reg[32].val>=(arch->segment[TEXT].startAddress+arch->segment[TEXT].size)){

		fprintf(stdout,"Error: Already at the end of the TEXT section\n");
		return 2;
		}

	return(execute_cmd_step(arch,liste));

	}
  
/* Execute_cmd_step */
int execute_cmd_step(mips* arch,Liste_Bp* liste){

	INFO_MSG("Entrée dans la fonction Execute_cmd_step");
   
	int procedure=0;
	int function=0;
	int instruction_int=0;
	void (*executor[128])(int,mips*);

	/* remplissage du tableau de fonctions */
	init_functionTab(arch,executor);
	 
	/* Récupération de l'instruction à l'adresse addr */
	instruction_int=getword(arch->reg[32].val,arch);

	/* Recherche de la commande à exécuter par l'opcode ou le function */
	int code=0;

	/* initialisation à typeR opcode=0 + shift dans le tableau des fonctions */
	code=getbits(instruction_int,26,31)+64;
		
	/* si non typeR alors typeIJ récupération de function */
	if(code==64){
		function=getbits(instruction_int,0,5);
		code=function;
		}
			
		
	/* Exécution de la commande */
	executor[code](instruction_int,arch);

	/* s'il y a une procédure : cad appel de jal */
	if (code==67){
	
	procedure=1;

		do {
			/* Récupération de l'instruction à l'adresse addr */		
			instruction_int=getword(arch->reg[32].val,arch);

			/* Recherche de la commande à exécuter par l'opcode ou le function */
			code=0;

			/* initialisation à typeR opcode=0 + shift dans le tableau des fonctions */
			code=getbits(instruction_int,26,31)+64;
				    
			/* si non typeR alors typeIJ récupération de function */
			if(code==64){
				function=getbits(instruction_int,0,5);
				code=function;
				}
						    
			/* Exécution de la commande */
			executor[code](instruction_int,arch);
			if(arch->reg[32].val==arch->reg[31].val){procedure=0;}
			  
			/* Incrémentation du PC */
			arch->reg[32].val=arch->reg[32].val+4;
	
			if(isBP(arch->reg[32].val,liste)==1){
				return CMD_OK_RETURN_VALUE;
				}

			}

			while(procedure);
	
		}
		
	else if(procedure==0 && code!=8 && code!=66){arch->reg[32].val=arch->reg[32].val+4;}

	
	return CMD_OK_RETURN_VALUE;
	
	}
  
	
	
 /* Parse_and_execute_step_into */
int parse_and_execute_cmd_stepInto(char* input ,mips* arch){

	INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_stepInto");
	char* pch;
	pch=strtok(input," ");
	
	if(pch!=NULL){
		fprintf(stdout,"Too Much argument\n");
		return 2;
		}
		
	if(arch->reg[32].val>=(arch->segment[TEXT].startAddress+arch->segment[TEXT].size)){

		fprintf(stdout,"Error: Already at the end of the TEXT section\n");
		return 2;
		}

	return(execute_cmd_stepInto(arch));
	
	}
  
/* execute_cmd_stepInto */  
int execute_cmd_stepInto(mips* arch){

	INFO_MSG("Entrée dans la fonction Execute_cmd_stepInto");
    	int instruction_int=0;
	void (*executor[128])(int,mips*);

	/* remplissage du tableau de fonctions */
	init_functionTab(arch,executor);
	 
	/* Récupération de l'instruction à l'adresse addr */
	instruction_int=getword(arch->reg[32].val,arch);

	/* Recherche de la commande à exécuter par l'opcode ou le function */
	int code=0;

	/* initialisation à typeR opcode=0 + shift dans le tableau des fonctions */
	code=getbits(instruction_int,26,31)+64;
	
	/* si non typeR alors typeIJ récupération de function */
	if(code==64){
		int function=0;
		function=getbits(instruction_int,0,5);
		code=function;
		}
		
	/* Exécution de la commande */
	executor[code](instruction_int,arch);

		  

	/* S'il y a une procédure : cad si appel de jal */
	
		if(code!=67 && code!=66 && code !=8 ){
		arch->reg[32].val=arch->reg[32].val+4; 
		}
				 
	return CMD_OK_RETURN_VALUE;
  
	}
  
/* parse_and_execute_erase */
int parse_and_execute_cmd_erase(char* input ,mips* arch,Liste_Bp* liste){

	INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_erase");

	/* déclaration des variables */ 	
	int i=0;
	char* pch;
	char* separators=" ";
	unsigned int arg1=0;
	unsigned int addr_in_block;
	
	pch=strtok(input," ");
	/* Test de la presence d'arguments*/
	if(pch==NULL){
		return execute_cmd_erase(-1,liste);
		}
	
	else if(pch[0]=='0' && pch[1]=='x'){
		pch=pch+2;
		}	
	else{
		fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n");
		return 2;
		}
	
	/* parsing de l'adresse */

	/* test longueur de l'argument 1 */
	if (strlen(pch)>8) { 
		fprintf(stdout,"Argument too long\n");
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
	/* si l'adresse est bien en héxadécimal */
	i=0;
	arg1=(unsigned int)strtol(pch,NULL,16);
	if(test_memoire(arch,arg1,&addr_in_block)!=TEXT){
		fprintf(stdout,"Warning : The address is not in the TEXT section!\n");
		return 2;
		}
	pch=strtok(NULL,separators);

	if(pch!=NULL){
		fprintf(stdout,"erase only takes one argument!\n");
		return 2;
		}
	
	return execute_cmd_erase(arg1,liste);
	
	}
  

	
int execute_cmd_erase(unsigned int addr,Liste_Bp* liste){

	INFO_MSG("Entrée dans la fonction Execute_cmd_erase");

	if(liste->nb_bp==0){
		fprintf(stdout,"There is no breakpoint to erase\n");
		return 2;
		}

	int trouve=0;
	Breakpoint *actuel = malloc(sizeof(*actuel));
	if(actuel==NULL){
		fprintf(stdout,"Impossible d'allouer un Breakpoint\n");
		exit(EXIT_FAILURE);
		}
	
	if(addr==-1){
		liste->nb_bp=0;
		liste->premier=NULL;
		trouve=1;
		}

	else{
		actuel=liste->premier;
		while(actuel!=NULL){
			if(actuel->addr==addr){
				eraseBP(liste,addr);
				trouve=1;
	      			}
		actuel=actuel->suivant;
		}
	}
	
	if(trouve!=1){
		fprintf(stdout,"No Breakpoint at the address 0x%x\n",addr);
		return 2;
		}
	
	return CMD_OK_RETURN_VALUE;
	
	}

/* erase_BP */
void eraseBP(Liste_Bp* liste, unsigned int addr){

	INFO_MSG("Entrée dans la fonction EraseBP");

	Breakpoint *actuel = malloc(sizeof(*actuel));	
	actuel=liste->premier;
	
	if(actuel->addr==addr){
		liste->premier=actuel->suivant;
		}
	
	else{
		while(actuel->suivant->addr!=addr){
			actuel=actuel->suivant;
			}
		actuel->suivant=actuel->suivant->suivant;
		}
	
	(liste->nb_bp)--;
	
	}

/* isBP */
int isBP( unsigned int addr, Liste_Bp* liste){

	int trouver=0;
	Breakpoint *actuel = malloc(sizeof(*actuel));
	
	actuel=liste->premier;
	
	while(actuel!= NULL){
		if(actuel->addr==addr){trouver=1;}
		actuel=actuel->suivant;
		}

	return trouver; 

	}

