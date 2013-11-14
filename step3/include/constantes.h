#ifndef __CONSTANTES_H__
#define __CONSTANTES_H__


/* Taille max pour nos chaines de char */
#define MAX_STR 1024

/* Valeur de retour speciales lorsqu'on pour la fonction int parse_and_execute_cmd_string(char *input); Toute autre valeur signifie qu'une erreur est survenue */
#define CMD_OK_RETURN_VALUE 0
#define CMD_EXIT_RETURN_VALUE -1
#define CMD_EMPTY_RETURN_VALUE -2
#define CMD_UNKOWN_RETURN_VALUE -3





/* prompt du mode shell interactif */
#define PROMPT_STRING "SimMipsShell : > "

#endif
