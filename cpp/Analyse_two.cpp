//
// Created by zy on 2021/8/22.
//
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include "../head_h/Analyse.h"
#include "../head_h/ReadHtml.h"

int Analyse_two(char *buf){
    char rex[1024]={0};
    int status;
    int cflags=REG_EXTENDED;
    regmatch_t pmatch[1];
    const size_t nmatch=1;
    regex_t  reg;

    const char* pattern="(/\\w*){0,}/(\\w*)(.html)|(/\\w*)(.html)|( / ){1}";
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