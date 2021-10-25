//
// Created by zy on 2021/8/22.
//
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include "../head_h/Analyse.h"
#include "../head_h/ReadHtml.h"

//GET /login.html HTTP/1.1
//Host: localhost:8080
//Connection: keep-alive
//sec-ch-ua: "Chromium";v="94", "Google Chrome";v="94", ";Not A Brand";v="99"
//sec-ch-ua-mobile: ?0
//sec-ch-ua-platform: "Linux"
//Upgrade-Insecure-Requests: 1
//User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
//Purpose: prefetch
//Sec-Fetch-Site: none
//Sec-Fetch-Mode: navigate
//Sec-Fetch-User: ?1
//Sec-Fetch-Dest: document
//Accept-Encoding: gzip, deflate, br
//Accept-Language: zh-CN,zh;q=0.9
//Cookie: Idea-3dc48b35=132c9a5e-adb1-45db-9ac9-f11782128c98

struct request _request;
int Analyse_two(char *buf);
int analyse_request(char* request);
char* analyse_request_method(char* request);
char* analyse_request_url(char* request);
char* analyse_request_protocol(char* request);
char* analyse_request_host(char* request);
char* analyse_request_addr(char* request);
char* analyse_request_port(char* request);
char* analyse_request_accept(char* request);
char* analyse_request_cookie(char* request);
char* analyse_request_accept_encoding(char* request);
char* analyse_request_accept_language(char* request);
char* analyse_request_parament(char* request);

int analyse_request(char* request){
     Analyse_two(request);
    char*url= analyse_request_method(request);
    char*protocol= analyse_request_url(url);
    char*host= analyse_request_protocol(protocol);
    char*addr= analyse_request_host(host);
    char*port= analyse_request_addr(addr);
    char*accept= analyse_request_port(port);
    char*accept_encoding= analyse_request_accept(accept);
    char* accept_language=analyse_request_accept_encoding(accept_encoding);

    char* cookie=analyse_request_accept_language(accept_language);
//    char* parament=
            analyse_request_cookie(cookie);
//    char* analyse_request_parament(char* request);
}
char* analyse_request_method(char* request){
    char* a=request;
    int len=strlen(request);
    char method[len]={0};//这里长度为request整体报文长度，但可以再优化，就是根据获取的不同行，获取当前行的大小
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]==' ')  {
            strncpy(method,a,i);
            break;
        }
    }
    _request.method=method;
    request=request+i+1;
    return request;
}

char* analyse_request_url(char* request){
    char* a=request;
    int len=strlen(request);
    char url[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]==' ')  {
            strncpy(url,a,i);
            break;
        }
    }
    _request.url=url;
    request=request+i+1;
    return request;
}
char* analyse_request_protocol(char* request){
    char* a=request;
    int len=strlen(request);
    char protocol[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]=='\n') //unix的换行为\n.windows为\r
        {
            strncpy(protocol,a,i);
            break;
        }
    }
    _request.protocol=protocol;
    request=request+i+1;
    return request;
}
char* analyse_request_host(char* request){
    char* a= nullptr;
    int len=strlen(request);
    char host[len]={0};//不影响
    for (int i = 0; i < len; ++i) {
        if (request[i]==' ') {
            request=request+i+1;
            a=request;
            break;
        }
    }//第一个循环去掉host:

    int t=0;
    int len1=strlen(request);
    for (; t < len1; ++t) {
        if (request[t] == '\n') {
            strncpy(host, a, t);
            break;
        }
    }
    _request.host=host;
    return request;
}
char* analyse_request_addr(char* request){
    char* a=request;
    int len=strlen(request);
    char addr[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]==':') //unix的换行为\n.windows为\r
        {
            strncpy(addr,a,i);
            break;
        }
    }
    _request.addr=addr;
    request=request+i+1;
    return request;
}
char* analyse_request_port(char* request){
    char* a=request;
    int len=strlen(request);
    char port[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]=='\n') //unix的换行为\n.windows为\r
        {
            strncpy(port,a,i);
            break;
        }
    }
    _request.port=port;
    request=request+i+1;
    return request;
    }
char* analyse_request_accept(char* request){
    int move=strspn(request,"Accept:");
    request=request+move;//指定到accept这一行

    char* a=request;
    int len=strlen(request);
    char accept[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]=='\n') //unix的换行为\n.windows为\r
        {
            strncpy(accept,a,i);
            break;
        }
    }
    _request.accept=accept;
    request=request+i+1;
    return request;
}
char* analyse_request_accept_encoding(char* request){
    int move=strspn(request,"Accept-Encoding:");
    request=request+move;//指定到accept这一行

    char* a=request;
    int len=strlen(request);
    char accept_encoding[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]=='\n') //unix的换行为\n.windows为\r
        {
            strncpy(accept_encoding,a,i);
            break;
        }
    }
    _request.accept_encoding=accept_encoding;
    request=request+i+1;
    return request;
}
char* analyse_request_accept_language(char* request){
    int move=strspn(request,"Accept-Language:");
    request=request+move;//指定到accept这一行

    char* a=request;
    int len=strlen(request);
    char accept_language[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]=='\n') //unix的换行为\n.windows为\r
        {
            strncpy(accept_language,a,i);
            break;
        }
    }
    _request.accept_language=accept_language;
    request=request+i+1;
    return request;
}
char* analyse_request_cookie(char* request){
    int move=strspn(request,"Accept-Language:");
    request=request+move;//指定到accept这一行

    char* a=request;
    int len=strlen(request);
    char cookie[len]={0};//不影响
    int i = 0;
    for (; i < len; ++i) {
        if (request[i]=='\n') //unix的换行为\n.windows为\r
        {
            strncpy(cookie,a,i);
            break;
        }
    }
    _request.cookie=cookie;
    request=request+i+1;
    return request;
}

char* analyse_request_parament(char* request){

}

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