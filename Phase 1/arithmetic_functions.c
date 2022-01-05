#include <stdlib.h>
#include <string.h>
#include <math.h>

int hex_to_dec (char * num)
{
  int res = 0, i = strlen(num) - 1, j = 0, po;
  while (i >= 0)
  {
    
    res += (int(num[i]) - '0') * int(pow(double(16),double(j)));
    i--;
    j++;
  }
  return res;
}

char * dec_to_hex (int a)
{
  int num = a, i = 0, j, test;
  char * tab, temp;
  tab = (char *) malloc (9 * sizeof(char));
  if (num == 0)
  {
    return "0";
  }
  while (num > 0)
  {
    tab[i] = (num % 16) + 48;
    num /= 16;
    i++;
  }
  tab[i] = '\0';
  i = 0;
  j = strlen(tab) - 1;
  while (i < j)
  {
    temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
    i++;
    j--;
  }
  return tab;
}