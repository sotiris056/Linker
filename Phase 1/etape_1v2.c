#include <stdio.h>
#include <elf.h>
#include <string.h>
#include <stdlib.h>
#include "etape_1v2.h"
#include "arithmetic_functions.h"
#include <stdint.h>
#include "util.h"

/*

//Magic Number
void get_magic_number(Elf32_Ehdr * header)
{
    printf(" Magic:    ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02X ", tab[i]);
    }
    printf("\n");
}

//Class
int get_class(Elf32_Ehdr * header)
{
    printf(" Class:                              ");
    switch(tab[4])
    {
        case 0:
            printf("Invalid\n");
            return 0;
        case 1:
            printf("ELF32\n");
            return 1;
        case 2:
            printf("ELF64\n");
            return 2;
    }
    return 0;
}
*/
//Data 
/*
void get_data(Elf32_Ehdr * header)
{
    printf(" Data:                               ");
    int data = header-> e_type;
    switch (data)
    {
        case 1 :
            printf("2's complement, little endian\n");
            break;
        case 2 :
            printf("2's complement, big endian\n");
            break;
        default :
            printf("Invalid data encoding\n");
    }
} */
/*
//Version
void get_version(char tab[64])
{
    printf(" Version:                            ");
    if (tab[6] == 1)
    {
        printf("%X (current)\n", tab[6]);
    }
    else
    {
        printf("Invalid version\n");
    }
}

//OS/ABI
void get_os_abi(char tab[64])
{
    printf(" OS/ABI:                             ");
    switch (tab[7]){
        case 0 :
            printf("UNIX - System V\n");
            break;
        case 1 :
            printf("HP-UX\n");
            break;
        case 2 :
            printf("NetBSD\n");
            break;
        case 3 :
            printf("Linux\n");  
            break;
        case 4:
            printf("GNU Hurd\n");
            break;
        case 6 :
            printf("Sun Solaris\n");
            break;
        case 7 :
            printf("IBM AIX\n");
            break;
        case 8 :
            printf("SGI Irix\n");
            break;
        case 9 :
            printf("FreeBSD\n");
            break;
        case 10 :
            printf("Compaq TRU64\n");
            break;
        case 11 :
            printf("Novell Modesto\n");
            break;
        case 12 :
            printf("OpenBSD\n");
            break;
        case 13:
            printf("OpenVMS\n");
            break;
        case 14:
            printf("NonStop Kernel\n");
            break;
        case 15:
            printf("AROS\n");
            break;
        case 16:
            printf("Fenix OS\n");
            break;
        case 17:
            printf("CloudABI\n");
            break;
        case 18:
            printf("Stratus Technologies OpenVOS");
            break;
        case 64 :
            printf("ARM EABI\n");
            break;
        case 97 :
            printf("ARM\n");
            break;
        case 255 :
            printf("Standalone\n");
            break;
    }
}

//Version ABI
void get_abi_version(char  tab[64])
{
    printf(" ABI Version :                       %X\n",tab[8]);
}

//Type (tab[16] + tab[17])
void get_type(char tab[64])
{
    printf(" Type :                              ");
    char str[17] = {'\0'};
    int elf_type;
    strcat(str, dec_to_hex(tab[16]));
    strcat(str, dec_to_hex(tab[17]));
    elf_type = hex_to_dec (str);
    switch (elf_type){
        case 1 :
            printf("REL (Relocatable file)\n");
            break;
        case 2 :
            printf("Executable\n");
            break;
        case 3 :
            printf("shared object\n");  
            break;
        case 4 :
            printf("Core file\n");
            break;
        default :
            printf("None\n");
            break;
    }
}


// Machine (tab[18] + tab[19])
void get_machine(char tab[64])
{
    printf(" Machine :                           ");
    int machine; // = (tab[18] * 10) + tab[19];
    char str[17] = {'\0'};
    strcat(str, dec_to_hex(tab[18]));
    strcat(str, dec_to_hex(tab[19]));
    machine = hex_to_dec (str);
    switch(machine){
        case 2 :
            printf("SPARC\n");
            break;
        case 3 :
            printf("Intel 80386\n");
            break;
        case 4 :
            printf("Motorola 68000\n");
            break;
        case 7 :
            printf("Intel i860\n");
            break;
        case 8 :
            printf("MIPS I\n");
            break;
        case 19 :
            printf("Intell i960\n");
            break;        
        case 20 :
            printf("PowerPC\n");
            break;
        case 40 :
            printf("ARM\n");
            break;
        case 50 :
            printf("Intel IA64\n");
            break;
        case 62 :
            printf("x64\n");
            break;
        case 243 :
            printf("RISC-V\n");
            break;
        default:
            printf("Invalid");    
    
    }
}

//Version machine (tab[20] - tab[23])
void get_version_machine(char tab[64])
{
    int version;
    char str[65] = {'\0'};
    for (int i = 20; i <= 23; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    version = hex_to_dec(str);
    printf(" Version :                           0x%X\n", version);
}

//Entry (tab[24]-tab[27] si 32bits (class = 1), tab[24]-tab[31] si 64bits (class = 2))
void get_entry(char tab[64]) {
    int entry_point=0;
    char str[65] = {'\0'};
    for (int i = 24; i <= 27; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    entry_point = hex_to_dec(str);

    printf(" Entry point address :               0x%X\n", entry_point);
} 

//Start of headers (tab[28] - tab[31] si 32bits, tab[32] - tab[39] si 64bits)
void get_start_header(char tab[64])
{
    int program_header = 0;
    char str[65] = {'\0'};
    for (int i = 28; i <= 31; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    program_header = hex_to_dec(str);

    printf(" Start of program headers :          %d (bytes into file) \n", program_header);
}

//Start of section header (tab[32] - tab[35] si 32bits, tab[40] - tab[47] si 64bits)
void get_start_section(char tab[64])
{
    int start_section = 0;
    char str[65] = {'\0'};
    for (int i = 32; i <= 35; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    start_section = hex_to_dec(str);
    printf(" Start of section headers :          %d (bytes into file) \n", start_section );
    
}

//Flags (tab[36] si 32bits, tab[48] si 64bits, 4bytes)
void get_flags(char tab[64])
{
    //int flags = 0;
    char str[65] = {'\0'};
    for (int i = 36; i <= 39; i++)
    {
        printf("%X", tab[i]);
        strcat(str, dec_to_hex(tab[i]));
    }
    printf("\n");
    //flags = hex_to_dec(str);
    //printf(" Flags :                             %x\n",flags);
}


//Size of header: tab[40] si 32bits,  tab[52] si 64bits, 2bytes
void get_size_of_header(char tab[64])
{
    int size_of_header = 0;
    char str[65] = {'\0'};
    for (int i = 40; i <= 41; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    size_of_header = hex_to_dec(str);
    printf(" Size of header :                    %d (bytes)\n",size_of_header);
  
}

//Size of program headers: tab[42] si 32bits, tab[54] si 64bits, 2bytes
void get_size_of_program(char tab[64])
{
    int program_header = 0;
    char str[65] = {'\0'};
    for (int i = 42; i <= 43; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    program_header = hex_to_dec(str);
    printf(" Size of program headers :           %d (bytes)\n",program_header);
      
}

//Number of program headers: tab[44] si 32bits, tab[56] si 64bits, 2bytes
void get_num_of_program_headers(char tab[64])
{
    int num_progam = 0;
    char str[65] = {'\0'};
    for (int i = 44; i <= 45; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    num_progam = hex_to_dec(str);
    printf(" Number of program headers :         %d\n",num_progam);
}

//Size of section headers: tab[46] si 32bits, tab[58] si 64bits, 2bytes
void get_size_of_section(char tab[64])
{
    int size_section = 0;
    char str[65] = {'\0'};
    for (int i = 46; i <= 47; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    size_section = hex_to_dec(str);
    printf(" Size of section headers :           %d (bytes)\n", size_section);

}

//Number of section headers: tab[48] si 32bits, tab[60] si 64bits, 2bytes
void get_num_section_headers(char tab[64])
{
    int num_section = 0;
    char str[65] = {'\0'};
    for (int i = 48; i <= 49; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    num_section = hex_to_dec(str);
    printf(" Number of program headers :         %d\n",num_section);
}

//Section header string table index: tab[50] si 32bits, tab[62] si 64bits, 2bytes
void get_section_table(char tab[64])
{
    int string_table = 0;
    char str[65] = {'\0'};
    for (int i = 50; i <= 51; i++)
    {
        strcat(str, dec_to_hex(tab[i]));
    }
    string_table = hex_to_dec(str);
    printf(" Section header string table index : %d\n",string_table);
}    
*/
int main (int argc , char * argv[])
{
    
    FILE * f = fopen(argv[1], "rb");
    if (f == NULL)
    {
        printf ("Erreur d'ouverture du fichier %s\n", argv[1]);
        return -1;
    }
    Elf32_Ehdr * header = (Elf32_Ehdr *) malloc (sizeof(Elf32_Ehdr));
    if (header == NULL)
    {
        printf("L'allocation a echoué\n");
        return 0;
    }
    fread(&header,sizeof(header),1,f);
    printf("ELF Header:\n");
    //Etape 1: Affichage de l'en-tête
/*


    get_header(f,header);
    get_magic_number(header);
    get_class(header);
*/   // get_data(header);
  /*  get_version(header);
    get_os_abi(header);
    get_abi_version(header);
    get_type(header);
    get_machine(header);
    get_version_machine(header);
    get_entry(header);
    get_start_header(header);
    get_start_section(header);
    get_flags(header);
    get_size_of_header(header);
    get_size_of_program(header);
    get_num_of_program_headers(header);
    get_size_of_section(header);
    get_num_section_headers(header);
    get_section_table(header);  */
    test(header);
    return 0;
} 