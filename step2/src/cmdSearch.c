#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <libelf.h> 
#include <math.h>

/* la librairie readline */ 
#include <readline/readline.h> 
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */ 
#include "global.h"
#include "libelf.h" 
#include "mipself.h" 
#include "notify.h" 
#include "structure.h" 
#include "constantes.h" 
#include "fonctions.h" 
#include "fonctionsStep1.h" 
#include "testsStep1.h" 
#include "fonctionsStep2.h" 
#include "elfimport.h"
#include "cmdSearch.h"

/* fonction cmdSearch */

char* cmdSearch(char* type, unsigned int param){

	INFO_MSG("Entering the function cmdSearch");

	/* déclaration des variables */
	char* current=malloc(4*sizeof(char));
	char* cmd=malloc(8*sizeof(char));
	char* cmdToExecute=malloc(8*sizeof(char));
	char* paramstr=malloc(4*sizeof(char));
	
	/* déclaration d'un flux */
	FILE *f=NULL;

	/* Selon le type on ouvre le fichier .desc correspondant */
	if(strcmp(type,"R")==0){f=fopen("./dictionnary/typeR.desc","r");}
	else if(strcmp(type,"IJ")==0){f=fopen("./dictionnary/typeIJ.desc","r");}
	else{return NULL;}

	/* gestion de l'erreur d'ouverture du flux */
	if(f==NULL){
		WARNING_MSG("Error opening the file");
		}
	else{
		/* passage du paramètre int en string */
		sprintf(paramstr,"%d",param);
		cmdToExecute=NULL;

		do {
			/* lecture d'une ligne du fichier .desc */
			fscanf(f,"%s %s",cmd,current);
			if(strcmp(current,paramstr)==0){cmdToExecute=strdup(cmd);}
			}
		/* tant que le current n'est pas trouvé */
		while(!feof(f) && strcmp(current,paramstr)!=0);
		}

	fclose(f);
	free(cmd);
	free(current);
	free(paramstr);
	INFO_MSG("Exiting the function cmdSearch");
	/* retourne un string instruction à réaliser */
	return cmdToExecute;
}
