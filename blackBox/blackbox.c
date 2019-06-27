#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>


int main()
{
    time_t t =time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year+1900, mon = tm.tm_mon+1, day=tm.tm_mday, hour=tm.tm_hour;
    int min=tm.tm_min;
    char s[1024];
    sprintf(s, "%d%d%d_%d%d",year,mon,day,hour,min);
    if(mkdir(s, 0776)==-1){
        printf("error()\n");
    }



    return 0;
}