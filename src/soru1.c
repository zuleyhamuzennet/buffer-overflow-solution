#include "stdlib.h"
#include "stdio.h"
#include "fields.h"
#include "string.h"

char** parseAddress(char* adresses)
{
    char *start = malloc(sizeof(char));
    char *end = malloc(sizeof(char));
    int ind = 0;
    int index = 0;
    int isStart = 0;
    while(adresses[ind] != NULL)
    {
        if(adresses[ind] == '-')
        {
            isStart = 1;
            index = 0;
            ind++;
        }
        if(isStart == 0)
        {
            start[index] = adresses[ind];
            ind++;
            index++;
        }
        else
        {
            end[index] = adresses[ind];
            ind++;
            index++;
        }
        
        
    }

    char** addresses = malloc(sizeof(char*));
    addresses[0] = start;
    addresses[1] = end;
    return addresses;
}

unsigned long calc_total_mem(unsigned long start,unsigned long end)
{
    return (unsigned long)(end-start);
}
int main(int argc,char** argv)
{
    void* start_data;
    void* end_data;
    unsigned long total_data = 0;

    char* proc_map = malloc(sizeof(char)*1000);
    sprintf(proc_map,"/proc/%d/maps",getpid());

    IS is;
    // mem** mems = malloc(sizeof(mem*));
    int mem_counter = 0;

    is = new_inputstruct(proc_map);

    while(get_line(is) > 0)
    {

        // printf("Satir : %d NF : %d ---> %s",is->line,is->NF,is->text1);
        // mem* m = malloc(sizeof(mem));

        for (int i = 0; i < is->NF; i++)
        {
            if(strcmp(is->fields[i],"[heap]")==0)
            {
                // printf("START END ADRES : %s %s\n",parseAddress(is->fields[0])[0],parseAddress(is->fields[0])[1]);
                void* start;
                void* end;
                sscanf(parseAddress(is->fields[0])[0],"%lx",(long unsigned *)&start );
                sscanf(parseAddress(is->fields[0])[1],"%lx",(long unsigned *)&end );

                unsigned long length = (unsigned long)(end-start);

                printf("Yığıt bölümü: başlangıç= %p, boyut = %d byte \n",start,length);
            }
            if(strcmp(is->fields[i],"[stack]")==0)
            {
                void* start;
                void* end;
                sscanf(parseAddress(is->fields[0])[0],"%lx",(long unsigned *)&start );
                sscanf(parseAddress(is->fields[0])[1],"%lx",(long unsigned *)&end );

                unsigned long length = (unsigned long)(end-start);
                printf("Yığın bölümü: başlangıç= %p, boyut = %d byte \n",start,length);
            }
            if(i == is->NF-1)
            {
                void* start;
                void* end;


                char* token;
                char* last;
                token = strtok(is->fields[i],"/");


                while(token != NULL)
                {
                    last = token;
                    token = strtok(NULL,"/");
                }

                if(strcmp(last,"soru1")==0)
                {
                    if(strcmp(is->fields[1],"rw-p")==0 )
                    {
                        void* start;
                        void* end;
                        sscanf(parseAddress(is->fields[0])[0],"%lx",(long unsigned *)&start );
                        sscanf(parseAddress(is->fields[0])[1],"%lx",(long unsigned *)&end );
                        total_data = total_data + (unsigned long)(end-start);
                    }
                    if (strcmp(is->fields[1],"r--p")==0)
                    {
                        sscanf(parseAddress(is->fields[0])[0],"%lx",(long unsigned *)&start_data );
                        sscanf(parseAddress(is->fields[0])[1],"%lx",(long unsigned *)&end_data );
                        total_data = total_data + (unsigned long)(end_data-start_data);
                    }
                    
                }


            }
        }
        
        
    }

    printf("Data bölümü: başlangıç= %p, boyut = %d byte \n",start_data,total_data);

    return 0;
}