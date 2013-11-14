#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__


int execute_cmd_testcmd(int hexValue);
int parse_and_execute_cmd_testcmd(char* paramsStr, mips* arch);
int execute_cmd_exit();
int parse_and_execute_cmd_exit(char* paramsStr);
int parse_and_execute_cmd_string(char* input, mips* arch);
int  acquire_line(FILE* fp, char* input);
void usage_ERROR_MSG(char* command) ;


#endif
