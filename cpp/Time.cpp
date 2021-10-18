//
// Created by zy on 2021/8/22.
//

#include <ctime>
#include <cstdio>
#include <cstring>


char* Date(char* date){
    time_t rawtime;
    struct tm * timeinfo;
    tzset();
    time (&rawtime );
    timeinfo = localtime ( &rawtime );
char buffer[128]={0};
    strftime(buffer,sizeof (buffer),"%a %F %X GMT\n",timeinfo);
//    printf("%s",buffer);
    strcat(date,"Date: ");
    strcat(date,buffer);
//    printf("%s",buffer);
    return date;
}

char* TimeFile(char* date){

//    fscanf_date(date);
    return Date(date);

}