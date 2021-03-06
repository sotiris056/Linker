#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include "etape_1.h"
#include "arithmetic_functions.h"
#include "util.h"

void get_header(FILE * in, char tab[65]) // tab en char unint32_t version =reverse() *(unint32_t *) &tab[8]) + renverser octet 
                                        // m2 mieux struct p18 doc + fread avec addresse header size of 
{
    int i = 0;
    char c; 
    while (i <= 64)
    {
        c = fgetc(in);
        tab[i] = c;
        i++;
    }
    tab[i] = '\0';
}

//Magic Number
char * get_magic_number(char tab[65])
{
    char * res = (char *) malloc (17 * sizeof(char));
    printf(" Magic:    ");
    for (int i = 0; i < 16; i++)
    {
        res[i] = tab[i];
        printf("%02X ", tab[i]);
    }
    res[16] = '\0';
    printf("\n");
    return res;
}

//Class
char get_class(char tab[65])
{
    printf(" Class:                              ");
    switch(tab[4])
    {
        case 0:
            printf("Invalid\n");
            return '0';
        case 1:
            printf("ELF32\n");
            return '1';
        case 2:
            printf("ELF64\n");
            return '2';
    }
    return '0';
}

//Data
char get_data(char tab[65])
{
    printf(" Data:                               ");
    switch (tab[5])
    {
        case 1 :
            printf("2's complement, little endian\n");
            return '1';
        case 2 :
            printf("2's complement, big endian\n");
            return '2';
        default :
            printf("Invalid data encoding\n");
            return '0';
    }
}

//Version
char get_version(char tab[65])
{
    printf(" Version:                            ");
    if (tab[6] == 1)
    {
        printf("%X (current)\n", tab[6]);
        return '1';
    }
    else
    {
        printf("Invalid version\n");
        return '0';
    }
}

//OS/ABI
int get_os_abi(char tab[65])
{
    printf(" OS/ABI:                             ");
    switch (tab[7]){
        case 0 :
            printf("UNIX - System V\n");
            return 0;
        case 1 :
            printf("HP-UX\n");
            return 1;
        case 2 :
            printf("NetBSD\n");
            return 2;
        case 3 :
            printf("Linux\n");  
            return 3;
        case 4:
            printf("GNU Hurd\n");
            return 4;
        case 6 :
            printf("Sun Solaris\n");
            return 6;
        case 7 :
            printf("IBM AIX\n");
            return 7;
        case 8 :
            printf("SGI Irix\n");
            return 8;
        case 9 :
            printf("FreeBSD\n");
            return 9;
        case 10 :
            printf("Compaq TRU64\n");
            return 10;
        case 11 :
            printf("Novell Modesto\n");
            return 11;
        case 12 :
            printf("OpenBSD\n");
            return 12;
        case 13:
            printf("OpenVMS\n");
            return 13;
        case 14:
            printf("NonStop Kernel\n");
            return 14;
        case 15:
            printf("AROS\n");
            return 15;
        case 16:
            printf("Fenix OS\n");
            return 16;
        case 17:
            printf("CloudABI\n");
            return 17;
        case 18:
            printf("Stratus Technologies OpenVOS");
            return 18;
        case 64 :
            printf("ARM EABI\n");
            return 64;
        case 97 :
            printf("ARM\n");
            return 97;
        case 255 :
            printf("Standalone\n");
            return 255;
        default:
            return -1;
    }
}

//Version ABI
char get_abi_version(char  tab[65])
{
    printf(" ABI Version :                       %X\n",tab[8]);
    return tab[8];
}

//Type (tab[16] + tab[17])
void get_type(char tab[65])
{
    //uint16_t * type;
    //type = (uint8_t) tab[16];
    //printf(" Type :                              ");
    
    //char str[17] = {'\0'};
    //int elf_type;
    uint16_t * type = &tab[16];
    uint16_t * ty = (type << 8) | (type >> 8);
    //type = reverse_2(type);
    printf("%x",*ty);
    //strcat(str, dec_to_hex(tab[16]));
    //strcat(str, dec_to_hex(tab[17]));
    //elf_type = hex_to_dec (str);
    /*switch (elf_type){
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
    }*/
}


// Machine (tab[18] + tab[19])
void get_machine(char tab[65])
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
void get_version_machine(char tab[65])
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
void get_entry(char tab[65]) {
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
void get_start_header(char tab[65])
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
void get_start_section(char tab[65])
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
void get_flags(char tab[65])
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
void get_size_of_header(char tab[65])
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
void get_size_of_program(char tab[65])
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
void get_num_of_program_headers(char tab[65])
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
void get_size_of_section(char tab[65])
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
void get_num_section_headers(char tab[65])
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
void get_section_table(char tab[65])
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

int main (int argc , char * argv[])
{
    
    FILE * f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf ("Erreur d'ouverture du fichier %s", argv[1]);
        return -1;
    }
    printf("ELF Header:\n");
    //Etape 1: Affichage de l'en-t??te

    char header[65], * magic_number, class, data , version , abi_version;
    int os_abi = -1;
    
    get_header(f,header);
    magic_number = get_magic_number(header);
    class = get_class(header);
    data = get_data(header);
    version = get_version(header);
    os_abi = get_os_abi(header);
    abi_version = get_abi_version(header);
    get_type(header);
    printf("%02X\n", abi_version);
    /*get_machine(header);
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
    get_section_table(header);*/
    return 0;
} 