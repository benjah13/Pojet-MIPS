#ifndef __SHELLSTEP3_H__
#define __SHELLSTEP3_H__


typedef struct Breakpoint Breakpoint;

struct Breakpoint{

	unsigned int addr; 
	Breakpoint *suivant;

	};


typedef struct Liste_Bp Liste_Bp;

struct Liste_Bp{

	Breakpoint *premier;
	Breakpoint *dernier;
	unsigned int nb_bp;

	};

int isBP( unsigned int addr, Liste_Bp* liste);
void Initialisation(unsigned int addr,Liste_Bp* liste);
int SetBP(Liste_Bp *liste, unsigned int addr1 );
void eraseBP(Liste_Bp* liste, unsigned int addr);



/*Run */

int parse_and_execute_cmd_run(char* input, mips* arch,Liste_Bp* liste);
int execute_cmd_run(unsigned int addr, mips* arch,Liste_Bp* liste);

/* Breakpoint*/
int parse_and_execute_cmd_bp(char* input,mips* arch,Liste_Bp* liste);
int execute_cmd_bp(unsigned int addr, mips* arch, Liste_Bp* liste);

/* Step */
int parse_and_execute_cmd_step(char* input ,mips* arch,Liste_Bp* liste);
int execute_cmd_step(mips* arch,Liste_Bp* liste);

/* step into */
int parse_and_execute_cmd_stepInto(char* input ,mips* arch);	
int execute_cmd_stepInto(mips* arch);

/* step into */
int parse_and_execute_cmd_erase(char* input ,mips* arch,Liste_Bp* liste);	
int execute_cmd_erase(unsigned int addr,Liste_Bp* liste);
	


/* delete breakpoint */
int execute_cmd_db(char* input, Liste_Bp* liste);


#endif
