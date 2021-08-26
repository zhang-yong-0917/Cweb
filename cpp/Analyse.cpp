//
// Created by zy on 2021/8/4.
//
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include "../head_h/File.h"
#include "../head_h/Reponsehttp.h"
#define MAXN 1024+10

char finall[1024]={0};
//int URL(char arr[]){
//
////    url=arr;
//}

int filterFacicon(char *buf){
    int status;
    int flag;
    int t=0;
    char arr[18];
    int cflags=REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch=1;
    regex_t  reg;

    const char* pattern="(/favicon.ico)";
    //编译正则模式
    regcomp(&reg,pattern,cflags);
    //执行正则表达式和缓存的比较
    status= regexec(&reg,buf,nmatch,pmatch,0);
    //打印匹配的字符串
    if (status == REG_NOMATCH) printf("favicon.ico No Match\n");
    else if(status == 0) {
        printf("Match:\n");
        for (int i = pmatch[0].rm_so; i <pmatch[0].rm_eo ; ++i){
            arr[t]=buf[i];
            ++t;
        }
    }
    flag= strcmp(arr,"/fvcicon.ico");
    regfree(&reg);
    return flag;
}
int urlAnalyse(char *buf);
int httpMsgAnalyse(char *buf);
int Analyse() {
    memset(finall,0,sizeof (finall));
    char *buf =fscanf(finall);
//    printf(buf);
    httpMsgAnalyse(buf);
//    urlAnalyse(buf);

}
int httpMsgAnalyse(char *buf){
    char rex[1024]={0};
    int status;
    int cflags=REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch=1;
    regex_t  reg;

    const char* pattern="(/\\w*){0,}/(\\w*)(\\.[A-Z a-z]* )|( / ){1}";
    //编译正则模式
    regcomp(&reg,pattern,cflags);
    //执行正则表达式和缓存的比较
    status= regexec(&reg,buf,nmatch,pmatch,0);
    //打印匹配的字符串
    if (status == REG_NOMATCH) printf("No Match\n");
    else if(status == 0) {
        printf("Match:\n");
        int t=0;
        for (int i = pmatch[0].rm_so; i <pmatch[0].rm_eo ; ++i){
            if (buf[i]==' '){
                ++t;
            } else{
                putchar(buf[i]);
                rex[t]=buf[i];
                ++t;
            }
        }
//        printf("url%s",rex);
        printf("\n");
        path(rex);
    }
    regfree(&reg);
    return 0;
}


int urlAnalyse(char *buf){
    int status;
    int cflags=REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch=1;
    regex_t  reg;

    const char* pattern="(/\\w*){0,}/(\\w*)(\\.[A-Z a-z]* )|( /){1}";
    //编译正则模式
    regcomp(&reg,pattern,cflags);
    //执行正则表达式和缓存的比较
    status= regexec(&reg,buf,nmatch,pmatch,0);
    //打印匹配的字符串
    if (status == REG_NOMATCH) printf("No Match\n");
    else if(status == 0) {
        printf("Match:\n");
        for (int i = pmatch[0].rm_so; i <pmatch[0].rm_eo ; ++i)
            putchar(buf[i]);
        printf("\n");
    }
    regfree(&reg);
    return 0;
}


