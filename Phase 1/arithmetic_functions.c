#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int hex_to_dec (char * num)
{
  int res = 0, i = strlen(num) - 1, j = 0;
  while (i >= 0)
  {
    if (num[i] >= 'A' && num[i] <= 'F')
    {
      res += (int) (num[i] - 55) * (int) (pow( (double) 16, (double) j ));
    }
    else
    {
      res += (int) (num[i] - '0') * (int) (pow( (double) 16, (double) j ));
    }
    i--;
    j++;
  }
  return res;
}

char * dec_to_hex (int a)
{
    int num = a, i = 0, j;
    char * tab, temp;
    tab = (char *) malloc (9 * sizeof(char));
    if (num == 0)
    {
        return "0";
    }
    while (num > 0)
    {
        if ((num % 16) >= 10)
        {
            switch (num % 16)
            {
                case 10:
                    tab[i] = 'A';
                    break;
                case 11:
                    tab[i] = 'B';
                    break;
                case 12:
                    tab[i] = 'C';
                    break;
                case 13:
                    tab[i] = 'D';
                    break;
                case 14:
                    tab[i] = 'E';
                    break;
                case 15:
                    tab[i] = 'F';
                    break;
            }
        }
        else
        {
            tab[i] = (num % 16) + 48;
        }
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