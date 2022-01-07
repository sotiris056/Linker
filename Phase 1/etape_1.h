#ifndef _etape_1_H_
#define _etape_1_H_
#include <stdio.h>

void get_header(FILE * in, char tab[65]);
char * get_magic_number(char tab[65]);
char get_class(char tab[65]);
char get_data(char tab[65]);
char get_version(char tab[65]);
int get_os_abi(char tab[65]);
char get_abi_version(char  tab[65]);
void get_type(char tab[65]);
void get_machine(char tab[65]);
void get_version_machine(char tab[65]);
void get_entry(char tab[65]);
void get_start_header(char tab[65]);
void get_start_section(char tab[65]);
void get_flags(char tab[65]);
void get_size_of_header(char tab[65]);
void get_size_of_program(char tab[65]);
void get_num_of_program_headers(char tab[65]);
void get_size_of_section(char tab[65]);
void get_num_section_headers(char tab[65]);
void get_section_table(char tab[65]);
void get_end_of_header(char tab[65]);
int main (int argc , char * argv[]);
#endif