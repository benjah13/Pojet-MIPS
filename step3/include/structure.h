#ifndef __STRUCTURE_H__
#define __STRUCTURE_H__

#define DATA 0
#define TEXT 1
#define BSS  2

/******************
Structure du MIPS
*******************/

/* typedef struct {
	unsigned int start_addr;
	unsigned int size;
	unsigned char* mem;
	} segment;
*/

typedef struct {
	unsigned int indice;
	char* mnemo;
	unsigned int val;
	} registre;

typedef struct {
	registre reg[36];
	SectionELF segment[3]; 
	} mips;

#endif
