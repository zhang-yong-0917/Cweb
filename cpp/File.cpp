//
// Created by zy on 2021/8/14.
//
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#define PATH "/home/zy/桌面/urltext.txt"


pthread_rwlock_t rwlock;
char httpmsg[1024]={0};

int fprintf_port(char *ip,int port)
{
    pthread_rwlock_wrlock(&rwlock);
    FILE *file= fopen(PATH,"w+");
    if(file == NULL)
    {
        printf("open error A!\n");
        return 0;
    }
    fprintf(file," %s:%d\n",ip,port);
    fclose(file);
    pthread_rwlock_unlock(&rwlock);
    return 0;
}
int fprintf_buf(char *buf)
{ pthread_rwlock_wrlock(&rwlock);
    FILE *fb= fopen(PATH,"a+");
    if(fb == NULL)
    {
        printf("open error B!\n");
        return 0;
    }
    fprintf(fb," %s\n",buf);
    fclose(fb);
    pthread_rwlock_unlock(&rwlock);
    return 0;
}
char *fscanf( char *finall){
    pthread_rwlock_rdlock(&rwlock);
    FILE *fp= fopen(PATH,"a+");;
    if(fp == NULL)
    {
        printf("open error C!\n");
        return 0;
    }

    while(fgets(httpmsg, 1024, fp) != NULL)
    {
//        memcpy(msg,finall,sizeof(msg));
        strcat(finall, httpmsg);
//        p.rintf("%s",msg);
    }
    fclose(fp);
    pthread_rwlock_unlock(&rwlock);
    return finall;
}
