#include "stdlib.h"
#include "stdio.h"
#include "fields.h"
#include "string.h"


char komutlar[5][50] = {
    "strcpy",
    "strcat",
    "sprintf",
    "gets",
    "getpw"
};

char alternatifler[5][50] = {
    "strlcpy(BSD library) yada strncpy",
    "strlcat(BSD library) yada strncat",
    "snprintf",
    "fgets",
    "getpwuid"
};

int kontrolEt(char* komut)
{
    komut = strtok(komut,"(");
    
    for (int i = 0; i < 5; i++)
    {
        if(strcmp(komutlar[i],komut) == 0)
        {
            return i;
        }
    }
    
    return -1;
}

int main(int argc,char** argv)
{
    IS is;
    is = new_inputstruct(argv[2]);

    char* param = argv[1];

    if(is == NULL)
    {
        printf("DOSYA BULUNAMADI ! \n");
        return -1;
    }
    while (get_line(is) >= 0)
    {
        for (int i = 0; i < is->NF; i++)
        {
                int index = kontrolEt(is->fields[i]);
            
                if(strcmp(param,"-r") == 0 && index != -1)
                {
                    printf("Satır %d: %s kullanılmış, yerine %s kullanmalısınız. \n",is->line,komutlar[index],alternatifler[index]);
                }
                if(strcmp(param,"-s") == 0 && index != -1)
                {
                    printf("Satır %d: %s kullanılmış. \n",is->line,komutlar[index]);
                }
                
        }
        
    }

}