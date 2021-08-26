//
// Created by zy on 2021/8/22.
//

#include <ctime>
#include <cstdio>
#include <cstring>

int fprintf_date(int year,int month, int day,int hour,int min,int sec,int wday )
{
    FILE *time_write= fopen("/home/zy/桌面/time.txt", "w+");
    if(time_write == NULL)
    {
        printf("open error F!\n");
        return 0;
    }
    fprintf(time_write, "%d %02d-%02d %4d %02d:%02d:%02d GMT\n", wday, day, month, year, hour, min, sec);
    fclose(time_write);
    return 0;
}
int Date(){
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime );
    timeinfo = localtime ( &rawtime );
    int year,month,day,hour,min,sec,wday;
    year = 1900+timeinfo->tm_year;
    month = 1+timeinfo->tm_mon;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    wday=timeinfo->tm_wday;

    fprintf_date(year,month,day,hour,min,sec,wday);

}

char *fscanf_date( char *date){
    char msg[100]={0};
    FILE *time_read= fopen("/home/zy/桌面/time.txt", "a+");;
    if(time_read == NULL)
    {
        printf("open error E!\n");
        return 0;
    }

    while(fgets(msg,100, time_read) != NULL)
    {
//        memcpy(msg,date,sizeof(msg));
        strcat(date, msg);
//        p.rintf("%s",msg);
    }
    fclose(time_read);
    remove("/home/zy/桌面/time.txt");
    return date;
}

char* TimeFile(char* date){
    Date();
    fscanf_date(date);
    return date;

}