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

/* FONCTIONS DONNEES DANS LE SUJET */

/* FONCTION TESTCMD */

/* EXECUTE TESTCMD */
int execute_cmd_testcmd(int hexValue){
	
	if(hexValue<=0){
		WARNING_MSG("command %s  - invalid call. The argument should be positive.\n", "test");
		return 2;
		}
	/* ecriture du resultat de la commande dans la sortie standard */
	fprintf(stdout, "CMD TEST RESULT 0x%x\n", hexValue + 1);
	
	return CMD_OK_RETURN_VALUE;
}

/* PARSE AND EXECUTE TESTCMD */
int parse_and_execute_cmd_testcmd(char* paramsStr, mips* arch){

	DEBUG_MSG("Parametres : %s",paramsStr);
	/* la commande test attend un argument hexa */
	int hexValue;
	if(sscanf(paramsStr,"%x",&hexValue)!=1){
	        WARNING_MSG("Invalid param : hexadecimal number awaited in '%s'\n", paramsStr);
	        return 2;
		}
	return execute_cmd_testcmd(hexValue);
}


/* FONCTION EXIT */

/* EXECUTE EXIT */
int execute_cmd_exit(){

	INFO_MSG("Bye bye !");
	return CMD_EXIT_RETURN_VALUE;
}

/* PARSE AND EXECUTE EXIT */
int parse_and_execute_cmd_exit(char* paramsStr){
	/*on ignore tous les parametres ! */
	return execute_cmd_exit();
}

/* FONCTION PARSE AND EXECUTE STRING */

/* @return CMD_OK_RETURN_VALUE si la commande s'est exécutée avec succès (0)
 * @return CMD_EXIT_RETURN_VALUE si c'est la commande exit. Dans ce cas, le programme doit se terminer (-1)
 * @return CMD_EMPTY_RETURN_VALUE si input n'a aucune commande (chaine vide) ou si commentaire (# qq chose) (-2)
 * @return CMD_UNKOWN_RETURN_VALUE si la commande n'est pas reconnue (-3)
 * @return tout autre nombre si erreur d'execution de la commande
 */
int parse_and_execute_cmd_string(char* input,mips* arch){

	DEBUG_MSG("input %s", input);
	char cmdStr[MAX_STR];
	memset( cmdStr, '\0', MAX_STR );

	/* gestion des commandes vides, commentaires, etc*/
	if(strlen(input)==0
           || sscanf(input,"%s",cmdStr)==0
           || strlen(cmdStr)==0
           || cmdStr[0]=='#'){return CMD_EMPTY_RETURN_VALUE;}

	/*parsing et execution des commandes !*/
	if(strcmp(cmdStr,"testcmd")==0){
	return parse_and_execute_cmd_testcmd(input + strlen(cmdStr),arch);
	}

	/* display memory */
	if(strcmp(cmdStr,"dm")==0){
	return parse_and_execute_cmd_dm(input + strlen(cmdStr),arch);
	}

    	/* display assembler */
	if(strcmp(cmdStr,"da")==0){
        return parse_and_execute_cmd_da(input + strlen(cmdStr),arch);
	}

    	/* display register */
    	if(strcmp(cmdStr,"dr")==0){
        return parse_and_execute_cmd_dr(input + strlen(cmdStr),arch);
	}

    	/* load memory */
   	if(strcmp(cmdStr,"lm")==0){
        return parse_and_execute_cmd_lm(input + strlen(cmdStr),arch);
    	}

    	/* load register */
	if(strcmp(cmdStr,"lr")==0){
        return parse_and_execute_cmd_lr(input + strlen(cmdStr),arch);
	}

	if(strcmp(cmdStr,"lp")==0){
        return parse_and_execute_cmd_lp(input + strlen(cmdStr),arch);
	}

    	/* exit */    
    	else if(strcmp(cmdStr,"quit")==0|| strcmp(cmdStr,"escape")==0 || strcmp(cmdStr,"ex")==0||strcmp(cmdStr,"exit")==0){
        return parse_and_execute_cmd_exit(input + strlen(cmdStr));
        }
        
        /* display assembler */
	if(strcmp(cmdStr,"man")==0){
        return man();
	}


    	WARNING_MSG("Unknown Command : '%s'\n",cmdStr);
    	return CMD_UNKOWN_RETURN_VALUE;
}

/* FONCTION ACQUIRE LINE */

/*
 * @return 0 si succes.
 * @return un nombre non nul si aucune ligne lue
 */
int  acquire_line(FILE *fp, char * input) {
    memset( input, '\0', MAX_STR );
    if ( stdin == fp ) {
        /* mode shell interactif */
        /* on utilise la librarie libreadline pour disposer d'un historique */
        char *chunk = readline( PROMPT_STRING );
        if (  strlen(chunk) == 0) {
            /* commande vide... */
            return 1;
        }
        /* ajout de la commande a l'historique, librairie readline */
        add_history( chunk );
        strcpy( input, chunk );

        free( chunk ); /* liberation de la mémoire allouée par la fonction readline() de libreadline */
    }
    else {
        /* mode fichier */
        /* acquisition d'une ligne dans le fichier */
        char * ret = fgets( input, MAX_STR, fp );
        if(ret == NULL) {
            return 1;
        }
if(strlen(ret) >0 && ret[strlen(ret) -1] == '\n') {
ret[strlen(ret)-1] = '\0';
}
    }
    DEBUG_MSG("Ligne acquise '%s'\n", input); /* macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG */
    return 0;
}

/* FONCTION D AFFICHAGE DU MESSAGE D ERREUR */
void usage_ERROR_MSG(char* command){

	fprintf(stderr,"Usage: %s[file.sim]\nIf no file is given, executes in Shell mode.",command);

}
