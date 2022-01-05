#ifndef _etape_1_H_
#define _etape_1_H_
#include <stdio.h>

void get_header(FILE * in, int tab[64]);
void get_magic_number(int tab[64]);
int get_class(int tab[64]);
void get_data(int tab[64]);
void get_version(int tab[64]);
void get_os_abi(int tab[64]);
void get_abi_version(int  tab[64]);
void get_type(int tab[64]);
void get_machine(int tab[64]);
void get_version_machine(int tab[64]);
void get_entry(int tab[64]);
void get_start_header(int tab[64]);
void get_start_section(int tab[64]);
void get_flags(int tab[64]);
void get_size_of_header(int tab[64]);
void get_size_of_program(int tab[64]);
void get_num_of_program_headers(int tab[64]);
void get_size_of_section(int tab[64]);
void get_num_section_headers(int tab[64]);
void get_section_table(int tab[64]);
void get_end_of_header(int tab[64]);
int main (int argc , char * argv[]);

#endif