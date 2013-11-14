#ifndef __EXECUTION_H__
#define __EXECUTION_H__

/* en-têtes des fonctions annexes */
int getword(unsigned int addr, mips* arch);
void setRegister(uint32_t indice, uint32_t valeur, mips* arch);
void SignalException(char* error, mips* arch);

/* en-têtes des fonctions d'exécution */
void execute_add(int word, mips* arch);
void execute_addi(int word, mips* arch);
void execute_and(int word, mips* arch);
void execute_beq(int word, mips* arch);
void execute_bgtz(int word, mips* arch);
void execute_blez(int word, mips* arch);
void execute_bne(int word, mips* arch);
void execute_div(int word, mips* arch);
void execute_j(int word, mips* arch);
void execute_jal(int word, mips* arch);
void execute_jr(int word, mips* arch);
void execute_lui(int word, mips* arch);
void execute_lw(int word, mips* arch);
void execute_mfhi(int word, mips* arch);
void execute_mflo(int word, mips* arch);
void execute_mult(int word, mips* arch);
void execute_nop(int word, mips* arch);
void execute_or(int word, mips* arch);
void execute_rotr(int word, mips* arch);
void execute_sll(int word, mips* arch);
void execute_slt(int word, mips* arch);
void execute_srl(int word, mips* arch);
void execute_sub(int word, mips* arch);
void execute_sw(int word, mips* arch);
void execute_syscall(int word, mips* arch);
void execute_xor(int word, mips* arch);

/* type pointeur sur fonction */
typedef void (*executor)(int,mips*);

/* init functionTab */
void init_functionTab(mips* arch,executor executor_t[128]);


#endif
