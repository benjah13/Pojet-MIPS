#ifndef __FONCTIONS_STEP_2__
#define __FONCTIONS_STEP_2__

/* GETBITS */
unsigned int getbits(unsigned int val, unsigned int start, unsigned int stop);

/* LOAD REGISTER */
int parse_and_execute_cmd_lr(char* input, mips* arch);
int execute_cmd_lr(int adr, unsigned int val, mips* arch);

/* DISPLAY REGISTER */
int parse_and_execute_cmd_dr(char* input, mips* arch);
int execute_cmd_dr(int test_reg, mips* arch);

/* CMDSEARCH */
char* cmdSearch(char* type, unsigned int param);

#endif
