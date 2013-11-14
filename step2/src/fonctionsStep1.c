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


/* INITIALISATION DU MIPS
   LOAD MEMORY
   DISPLAY MEMORY
   LOAD REGISTER
   DISPLAY REGISTER
   DISPLAY ASSEMBLER */




/***********************************************/
/***** FONCTION D INITIALISATION DU MIPS *****/
/********************************************/

void init_mips(mips* arch){

	init_segment(&arch->segment[DATA], DATA);
	init_segment(&arch->segment[TEXT], TEXT);
	init_segment(&arch->segment[BSS], BSS);

	int i;
	for(i=0;i<35;i++){arch->reg[i].indice=i;}
	for(i=0;i<35;i++){arch->reg[i].val=0;}
	for(i=0;i<35;i++){arch->reg[i].mnemo=malloc(4*sizeof(char));}
	arch->reg[0].mnemo="zero";
	arch->reg[1].mnemo="at";
	arch->reg[2].mnemo="v0";
	arch->reg[3].mnemo="v1";
	arch->reg[4].mnemo="a0";
	arch->reg[5].mnemo="a1";
	arch->reg[6].mnemo="a2";
	arch->reg[7].mnemo="a3";
	arch->reg[8].mnemo="t0";
	arch->reg[9].mnemo="t1";
	arch->reg[10].mnemo="t2";
	arch->reg[11].mnemo="t3";
	arch->reg[12].mnemo="t4";
	arch->reg[13].mnemo="t5";
	arch->reg[14].mnemo="t6";
	arch->reg[15].mnemo="t7";
	arch->reg[16].mnemo="s0";
	arch->reg[17].mnemo="s1";
	arch->reg[18].mnemo="s2";
	arch->reg[19].mnemo="s3";
	arch->reg[20].mnemo="s4";
	arch->reg[21].mnemo="s5";
	arch->reg[22].mnemo="s6";
	arch->reg[23].mnemo="s7";
	arch->reg[24].mnemo="t8";
	arch->reg[25].mnemo="t9";
	arch->reg[26].mnemo="k0";
	arch->reg[27].mnemo="k1";
	arch->reg[28].mnemo="gp";	
	arch->reg[29].mnemo="sp";
	arch->reg[30].mnemo="fp";
	arch->reg[31].mnemo="ra";
	arch->reg[32].mnemo="pc";
	arch->reg[33].mnemo="hi";
	arch->reg[34].mnemo="lo";

}

void init_segment(SectionELF* seg, int type){

	int i;
	switch(type){

	case DATA:
	seg->startAddress=400;
	seg->size=100;
	seg->data=malloc((seg->size)*sizeof(BYTE));
	
	for(i=0;i<seg->size;i++){
		seg->data[i]=0x00;
		}
	break;

	case TEXT:
	seg->startAddress=200;
	seg->size=100;
	seg->data=malloc((seg->size)*sizeof(BYTE));
	
	for(i=0;i<seg->size;i++){
		seg->data[i]=0x00;
		}
	break;

	case BSS:
	seg->startAddress=0;
	seg->size=100;
	seg->data=malloc((seg->size)*sizeof(BYTE));
	
	for(i=0;i<seg->size;i++){
		seg->data[i]=0x00;
		}
	break;

	default:
	break;
	}
}



/**********************************/
/***** FONCTIONS LOAD MEMORY *****/
/*********************************/


/* EXECUTE LOAD MEMORY */
int execute_cmd_lm(unsigned int adr, unsigned int val, mips* arch){
INFO_MSG("Entrée dans la fonction Execute_cmd_lm");
	unsigned int addr_in_block;
	
	switch(test_memoire(arch, adr, &addr_in_block)){

	case -1:
	fprintf(stdout,"This address isn't in an allocated segment\n");
	break;

	case BSS:
	arch->segment[BSS].data[addr_in_block] = val;
	fprintf(stdout,"The value %x has been loaded in the address 0x%x\n", val,adr);
	break;

	case DATA:
	arch->segment[DATA].data[addr_in_block] = val;
	fprintf(stdout,"The value %x has been loaded in the address 0x%x\n", val,adr);
	break;

	case TEXT:
	arch->segment[TEXT].data[addr_in_block] = val;
	fprintf(stdout,"The value %x has been loaded in the address 0x%x\n", val,adr);
	break;
	}
	return CMD_OK_RETURN_VALUE;
}

/* PARSE AND EXECUTE LOAD MEMORY */
int parse_and_execute_cmd_lm(char* paramsStr, mips* arch){
INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_lm");

	char *separators=" ";
	char *pch;
	int cpt=0,i=1;
	pch=strtok(paramsStr,separators);
	
	/* Test de la presence d'arguments*/
	if(pch==NULL){
	 fprintf(stdout,"Too few arguments\n");
	return 2;
	}
	/* si l'adresse commence par '0x' on décale le pointeur de 2 caractères */
	if(pch[0]=='0' && pch[1]=='x'){pch=pch+2;}
	else{fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n"); return 2;}

	unsigned int c1, c2;
	unsigned int addr_in_block;

	while(pch!=NULL){
	
	DEBUG_MSG("Parametres : %s", pch);

	/* compteur incrémenté sur l'argument lu après la commande lm */
	switch(cpt){

	case 0 :
	/* test adresse */
	c1=(unsigned int)strtol(pch,NULL,16);
	if(test_memoire(arch,c1,&addr_in_block)<0){
		fprintf(stdout,"Warning : The address is not allocated for the simulator!\n");
		return 2;
		}
		
	/* teste si l'adresse est hexadécimale */
	while (pch[i]!='\0'&& pch[i]!='\n'){
		if(!isxdigit(pch[i])){
			fprintf(stdout,"Invalid param : hexadecimal number awaited in %s\n", pch);
			return 2;
			}
		i++;
		}
	cpt++;
	pch=strtok(NULL,separators);
	if(pch==NULL){fprintf(stdout,"too few arguments\n");}
	break;

	case 1 :
	  i=0;
	  
	/* si l'adresse commence par '0x' on décale le pointeur de 2 caractères */
	if(pch[0]=='0' && pch[1]=='x'){pch=pch+2;}
	else{fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n"); return 2;}
 
	/* test valeur */
	while (pch[i]!='\0'&& pch[i]!='\n'){
		if(!isxdigit(pch[i])){
			fprintf(stdout,"Invalid param : hexadecimal number awaited in %s\n", pch);
			return 2;
			}
		i++;
		}
	
	c2=(unsigned int)strtol(pch,NULL,16);
	
	/* test argument valeur compris entre 0 et 255 */
	if(test_valeur(c2)<0){
		fprintf(stdout,"Error : The 2nd argument of lm isn't a valide value\n");
		return 2;
		}
	/* test nombre d'arguments == 2 */	
	pch=strtok(NULL,separators);
	cpt=0;

	if(pch!=NULL){
		fprintf(stdout,"LM function only takes two arguments\n");
		return 2;
		}
	break;
	}	
	}
	/* execution de la commande */
	return execute_cmd_lm(c1,c2,arch);
}



/**************************************/
/***** FONCTIONS DISPLAY MEMORY ******/
/*************************************/


int execute_cmd_dm(int cas, unsigned int addr, unsigned int arg2, mips* arch){
INFO_MSG("Entrée dans la fonction Execute_cmd_dm");

	unsigned int addr_in_block=0;
	unsigned char valeur=0;
	int cpt=1,j=0;
  
	switch(cas){
 
	case 3:
	/* une seule adresse mémoire */
	switch(test_memoire(arch,addr,&addr_in_block)){
			
		case -1:
		fprintf(stdout,"%08x:	00", addr);
		break;
			      
		case BSS:
		valeur=arch->segment[BSS].data[addr_in_block];
		fprintf(stdout,"%08x:	%02x\n", addr, valeur);
		break;
				      
		case DATA:
		valeur=arch->segment[DATA].data[addr_in_block];
		fprintf(stdout,"%08x:	%02x\n", addr, valeur);
		break;
			
		case TEXT:
		valeur=arch->segment[TEXT].data[addr_in_block];
		fprintf(stdout,"%08x:	%02x\n", addr, valeur);
		break;
		}
		
		break;

	case 1:
	/* séparateur ':' */
		fprintf(stdout,"%08x:	", addr);
						  
		for(j=0;j<arg2;j++){
		/* affichage de 16 éléments par ligne */
		if(cpt==17){
			fprintf(stdout,"\n%08x:	", addr+j);
			cpt=1;
		   	}
		      
		switch(test_memoire(arch,addr+j,&addr_in_block)){
			
		case -1:
		fprintf(stdout,"00 ");
		break;
							
		case BSS:
		valeur=arch->segment[BSS].data[addr_in_block];
		fprintf(stdout,"%02x ", valeur);
		break;
						
		case DATA:
		valeur=arch->segment[DATA].data[addr_in_block];
		fprintf(stdout,"%02x ", valeur);
		break;
							
		case TEXT:
		valeur=arch->segment[TEXT].data[addr_in_block];
		fprintf(stdout,"%02x ", valeur);
		break;
		}
		
		cpt++;
		}
	
		fprintf(stdout,"\n");	
	  	break;
  
  
	case 2:
	/* séparateur '~' */
		fprintf(stdout,"%08x:	", addr+j);	

		while(arg2+1-(addr+j)>0){
	    	/* affichage de 16 éléments par ligne */
		if(cpt==17){
			fprintf(stdout,"\n%08x:	", addr+j);
			cpt=1;
		}

		switch(test_memoire(arch,addr+j,&addr_in_block)){

		case -1:
		fprintf(stdout,"00 ");
		break;
							
		case BSS:
		valeur=arch->segment[BSS].data[addr_in_block];
		fprintf(stdout,"%02x ", valeur);
		break;
							
		case DATA:
		valeur=arch->segment[DATA].data[addr_in_block];
		fprintf(stdout,"%02x ", valeur);
		break;
							
		case TEXT:
		valeur=arch->segment[TEXT].data[addr_in_block];
		fprintf(stdout,"%02x ", valeur);
		break;
		}
			      
		cpt++;	
		j++;
		}

	fprintf(stdout,"\n");
    	break; 

	default:
	break;
	}
 
	return CMD_OK_RETURN_VALUE;
}


/* PARSE AND EXECUTE DISPLAY MEMORY */
int parse_and_execute_cmd_dm(char *paramsStr, mips* arch){
INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_dm");

	/* déclaration des variables */ 	
	int i=0;
	int cas=0;
	char* pch;
	char* separators="\n";
	unsigned int arg1=0,arg2=0;
	unsigned int addr_in_block;
	
	pch=strtok(paramsStr," ");
	/* Test de la presence d'arguments*/
	if(pch==NULL){
	 fprintf(stdout,"Too few arguments\n");
	return 2;
	}
	
	else if(pch[0]=='0' && pch[1]=='x'){
		pch=pch+2;
		}	
	else{fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n"); return 2;}

	/* définition du cas et du séparateur */
	if(strchr(pch,':')!=NULL){separators=":"; cas=1;}
	else if(strchr(pch,'~')!=NULL){separators="~"; cas=2;}
	else {cas=3;}

	/* parsing de l'adresse */
	pch=strtok(pch,separators);
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
	if(test_memoire(arch,arg1,&addr_in_block)<0){
		fprintf(stdout,"Warning : The address is not allocated for the simulator!\n");
		return 2;
		}
	pch=strtok(NULL,separators);
	  	
	switch(cas){
	
	case 0:
	break;

	case 1:
	/* séparateur ':' */
	while(pch[i]!='\0' && pch[i]!='\n'){	
		if(!isdigit(pch[i])){
			fprintf(stdout,"Invalid param : decimal number awaited in '%s'\n", pch);
			return 2;
			}
		i++;
		}
	arg2=(unsigned int)strtol(pch,NULL,10);
	break;	
	
	case 2:
	/* séparateur '~' */
	if(pch[0]=='0' && pch[1]=='x'){
		pch=pch+2;
		}
	else{fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n"); return 2;}

	
	while(pch[i]!='\0' && pch[i]!='\n'){
		if(!isxdigit(pch[i])){
			fprintf(stdout,"Invalid param : hexadecimal number awaited in '%s'\n", pch);
			return 2;
			}
		i++;
		}
	arg2=(unsigned int)strtol(pch,NULL,16);
	/* test arg2>arg1 */
	if(arg2<arg1){
		fprintf(stdout,"Invalid param : arg2 lower than arg1\n");
		return 2;
		}
	break;

	default:
	break;
	}

	return execute_cmd_dm(cas,arg1,arg2,arch);
}




/***************************************/
/***** FONCTIONS DISPLAY REGISTER *****/
/**************************************/

/* EXECUTE DISPLAY REGISTER */
int execute_cmd_dr(int test_reg, mips* arch){
INFO_MSG("Entrée dans la fonction Execute_cmd_dr");

	int i=0;

	/* registre inconnu */
	if(test_reg==-3){
		fprintf(stdout,"Unknown register\n");
		return 2;
		}

	/* affichage de tous les registres */
	else if(test_reg==-2){
		for(i=0;i<35;i++){
			fprintf(stdout,"$%s	$%d	%x\n" ,arch->reg[i].mnemo,arch->reg[i].indice,arch->reg[i].val);
		}
	}

	/* erreur de notation */ 
	else if(test_reg==-1){
		fprintf(stdout,"A register should begin by $\n");
		return 2;
		}
	else {
		fprintf(stdout,"$%s	$%d	%x\n" ,arch->reg[test_reg].mnemo,arch->reg[test_reg].indice,arch->reg[test_reg].val);
	}
    
	return CMD_OK_RETURN_VALUE;
}

/* PARSE AND EXECUTE DISPLAY REGISTER */
int parse_and_execute_cmd_dr(char* input, mips* arch){
  INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_dr");

	char* pch;
	char* separators=" ";
 	pch=strtok(input,separators);

	/* appels successifs de la fonction execute_cmd_dr */
	do {    
		/* si l'éxécution aboutit à une erreur, on retourne 2 (code erreur) */  
		if(execute_cmd_dr(test_registre(pch),arch)==2){
			return 2;
			}
		pch=strtok(NULL, separators);
      		}
	
	while(pch!=NULL);
	
	return CMD_OK_RETURN_VALUE;
	}


	
	
/************************************/
/***** FONCTIONS LOAD REGISTER *****/
/**********************************/



/* EXECUTE LOAD REGISTER */
int execute_cmd_lr(int adr,unsigned int val,mips* arch){
INFO_MSG("Entrée dans la fonction Execute_cmd_lr");

  if(adr==0)
  {
    fprintf(stdout,"The registre $0 cannot be modified!\n");
    return 2;
  }
	arch->reg[adr].val=val;
	fprintf(stdout,"The value %x has been loaded in register $%d\n",val,adr);
	
	return CMD_OK_RETURN_VALUE;

}

/* PARSE AND EXECUTE LOAD REGISTER */
int parse_and_execute_cmd_lr(char* input, mips* arch){
  
INFO_MSG("Entrée dans la fonction parse_and_Execute_cmd_lr");

	char* separators=" ";
	char* pch;
	int cpt=0;
	int c1=0;
	int i=0;	
	unsigned int c2;	

	pch=strtok(input,separators);	
	/* Test de la presence d'arguments*/
	if(pch==NULL){
	 fprintf(stdout,"Too few arguments\n");
	return 2;
	}
	
	c1=test_registre(pch);

	while(pch!=NULL){
	
	DEBUG_MSG("Parametres : %s", pch);

	/* compteur incrémenté sur l'argument lu */
	switch(cpt){

	case 0 :
	/* test adresse */
	if(c1<0){
		fprintf(stdout,"Error : the first argument isn't a valide register name\n");
		return 2;
		}
	cpt++;
	pch=strtok(NULL,separators);
	break;

	case 1 :
	  
	  if(pch[0]=='0' && pch[1]=='x'){
		pch=pch+2;
		}
	else{fprintf(stdout,"Error : An Hexadecimal should start by '0x'\n"); return 2;}

	c2=(unsigned int)strtoul(pch,NULL,16);
		
	/* test valeur */
	
	while (pch[i]!='\0' && pch[i]!='\n'){
	
		if(!isxdigit(pch[i])){
			fprintf(stdout,"Invalid param : hexadecimal number awaited in %s\n", pch);
			return 2;
			}
		i++;
		}

	/* test longueur de l'argument 1 */
	if (strlen(pch)>8) { 
		fprintf(stdout,"Argument 2 too long\n");
		return 2;
		}
		
	pch=strtok(NULL,separators);
	cpt=0;
	if (pch!=NULL){
		fprintf(stdout,"Warning : LR function only takes two arguments\n");
	 	return 2;
		}
	break;
	}	
	}
	/* execution de la commande */
	return execute_cmd_lr(c1,c2,arch);
}
