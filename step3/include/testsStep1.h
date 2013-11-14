#ifndef __FONCTIONS_TESTS_H__
#define __FONCTIONS_TESTS_H__

/* FONCTION TEST REGISTRE */
int test_registre(char* input);

/* FONCTION TEST MEMOIRE */
int test_memoire(mips *arch, unsigned int adresse, unsigned int *addr_in_block);

/* FONCTION TEST VALEUR */
int test_valeur(unsigned int val);

#endif
