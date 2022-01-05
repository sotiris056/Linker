#include <stdio.h>
#include <elf.h>
#include "etape_1.h"
#include "arithmetic_functions.h"

void get_header(FILE * in, int tab[64])
{
    int i = 0;
    char c;
    while (i < 64)
    {
        c = fgetc(in);
        tab[i] = c;
        i++;
    }
}

//Magic Number
void get_magic_number(int tab[64])
{
    printf(" Magic:    ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02X ", tab[i]);
    }
    printf("\n");
}

//Class
int get_class(int tab[64])
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
}

//Data
void get_data(int tab[64])
{
    printf(" Data:                               ");
    switch (tab[5])
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
}

//Version
void get_version(int tab[64])
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
void get_os_abi(int tab[64])
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
void get_abi_version(int  tab[64])
{
    printf(" ABI Version :                       %X\n",tab[8]);
}

//Type (tab[16] + tab[17])
void get_type(int tab[64])
{
    printf(" Type :                              ");
    int elf_type = (tab[16] * 10) + tab[17];
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
void get_machine(int tab[64])
{
    printf(" Machine :                           ");
    int machine = (tab[18] * 10) + tab[19];
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
void get_version_machine(int tab[64])
{
    int i = 20, j = 1000 , version = 0;
    while (i <= 23)
    {
        version += (tab[i] * j);
        i++;
        j = j / 10;
    }
    printf(" Version :                           0x%X\n", version);
}

//Entry (tab[24]-tab[27] si 32bits (class = 1), tab[24]-tab[31] si 64bits (class = 2))
void get_entry(int tab[64]) {
    int i = 24 ; 
    int entry_point=0;
    if (tab[4] == 1)
    {
        int j = 1000;
        while (i <= 27)
        {
            entry_point += (tab[i] * j);
            i++;
            j = j / 10;
        }
    }
    else
    {
        int j = 10000000;
        while (i <= 31)
        {
            entry_point += (tab[i] * j);
            i++;
            j = j / 10;
        }
    }
    printf(" Entry point address :               0x%X\n", entry_point);
} 

//Start of headers (tab[28] - tab[31] si 32bits, tab[32] - tab[39] si 64bits)
void get_start_header(int tab[64])
{
    int program_header = 0;
    if (tab[4] == 1)
    {
        int i = 28;
        int j = 1000;
        while (i <= 31)
        {
            program_header += (tab[i] * j);
            i++;
            j = j / 10;
        }
    }
    else
    {
        int i = 32;
        int j = 10000000;
        while (i <= 39)
        {
            program_header += (tab[i] * j);
            i++;
            j = j / 10;
        }
    }
    printf(" Start of program headers :          %X (bytes into file) \n", program_header);
}
//Start of section header (tab[32] - tab[35] si 32bits, tab[40] - tab[47] si 64bits)
void get_start_section(int tab[64])
{
    int section_header = 0;
    /*for (int i = 32; i <= 35; i++)
    {
        printf("%d\n", tab[i]);
    }*/
    if (tab[4] == 1)
    {
        int i = 32;
        int j = 1000;
        while (i <= 35)
        {
            section_header += (tab[i] * j);
            i++;
            j = j / 10;
        }
    }
    else
    {
        int i = 40;
        int j = 10000000;
        while (i <= 47)
        {
            section_header += (tab[i] * j);
            i++;
            j = j / 10;
        }
    }
    printf(" Start of section headers :          %X (bytes into file) \n",section_header );
    
}

//Flags (tab[36] si 32bits, tab[48] si 64bits, 4bytes)
void get_flags(int tab[64])
{
    printf(" Flags :                             |\n");
}


//Size of header: tab[40] si 32bits,  tab[52] si 64bits, 2bytes
void get_size_of_header(int tab[64])
{
    if (tab[4] == 1)
    {
        int size_of_header = (hex_to_dec(10*(tab[40])) + hex_to_dec(tab[41]));
        printf(" Size of header :                    %x (bytes)\n",size_of_header);
    }
    else
        printf(" Size of header2 :                    %x\n(bytes)",tab[51]);
}

//Size of program headers: tab[42] si 32bits, tab[54] si 64bits, 2bytes
void get_size_of_program(int tab[64])
{
    if (tab[4] == 1)
        printf(" Size of program headers :           %x (bytes)\n",tab[42]);
    else
        printf(" Size of program headers :           %x (bytes)\n",tab[54]);     
}

//Number of program headers: tab[44] si 32bits, tab[56] si 64bits, 2bytes
void get_num_of_program_headers(int tab[64])
{
    if (tab[4] == 1)
        printf(" Number of program headers :         %x\n",tab[44]);
    else
        printf(" Number of program headers :         %x\n",tab[56]);

}

//Size of section headers: tab[46] si 32bits, tab[58] si 64bits, 2bytes
void get_size_of_section(int tab[64])
{
    if (tab[4] == 1)
        printf(" Size of section headers :           %x\n",tab[46]);
    else 
        printf(" Size of section headers :           %x\n",tab[58]);
}
    
    
//Number of section headers: tab[48] si 32bits, tab[60] si 64bits, 2bytes
void get_num_section_headers(int tab[64])
{
    printf(" Number of program headers :         |\n");
}


//Section header blablabla: tab[50] si 32bits, tab[62] si 64bits, 2bytes
void get_section_table(int tab[64])
{

    printf(" Section header string table index : |\n");
}    
    
    
    

//End of header: tab[52] si 32bits, tab[64] si 64bits
void get_end_of_header(int tab[64])
{
    printf(" End of headers :                    | \n");
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
    //Etape 1: Affichage de l'en-tête

    int header[64];

    get_header(f,header);
    get_magic_number(header);
    get_class(header);
    get_data(header);
    get_version(header);
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
    get_section_table(header);
    get_end_of_header(header);

    
    return 0;
} 