#ifndef __FONCTIONS_STEP_1__
#define __FONCTIONS_STEP_1__


/* DECLARATION DES FONCTIONS POUR STEP1 */

/* INITIALISATION DU MIPS */
void init_mips(mips* arch);
void init_segment(SectionELF* seg, int type);

/* LOAD PROGRAM */
int parse_and_execute_cmd_lp(char* input, mips* arch);
int execute_cmd_lp(FILE* program , char *nom_fichier ,mips *arch);

/* LOAD MEMORY */
int parse_and_execute_cmd_lm(char* input, mips* arch);
int execute_cmd_lm(unsigned int adr, unsigned int val, mips *arch);

/* DISPLAY MEMORY */
int parse_and_execute_cmd_dm(char* input, mips* arch);
int execute_cmd_dm(int cas, unsigned int addr, unsigned int arg2, mips* arch);

/* DISPLAY ASSEMBLEUR */
int parse_and_execute_cmd_da(char* input, mips* arch);
int execute_cmd_da(unsigned int addr, unsigned int nbr_instr, mips* arch);



#endif
