#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "time.h"
#include "../head_h/Time.h"
#include "../head_h/servlet.h"
//
// Created by zy on 2021/8/18.
//

//struct s_http_response * http_response=(s_http_response *) malloc(sizeof (s_http_response));
struct s_http_response  http_response;
struct s_http_request http_request;


void set_status(char *__rps);
void  set_header(char *__rps);
void set_body( char *__rps);
void set_ContentType(char *__rps);
void set_cookie( char *__rps);
void set_location(char *__rps);

char* do_spell(char* reponse);
char * ResponseSpell(char* buf){
    memset(buf,0,sizeof (buf));

    //当程序员未调用的时候，默认自己调用
    do_spell(buf);//开始拼写
//    strcat(reponse,buf);//拼接
    return buf;
}


char* do_spell(char *reponse){

//    (s_http_response*) malloc(sizeof (http_response));
    char* swap[100]={0};
    char date[100]={0};

//    *swap="HTTP/1.1 200 ok\n";
//    memset(swap,0,sizeof (swap));
    printf(http_response.status);
    strcat(reponse,http_response.status); //设置响应头
    //当没用任何人调用时候为空指针异常

    TimeFile(date);//获取时间
    *swap="Date: ";
//    strcat(reponse,*swap);
    strcat(reponse,date);

    printf(http_response.ContentType);
    strcat(reponse,http_response.ContentType);

    strcat(reponse,http_response.cookie);
//    "Content-Type: text/html;charset=UTF-8\n"
    *swap="Connection: keep-alive  \n"
          "Server: squid/3.5.24\n"
          "vary:Accept-Encoding";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));

    *swap="Expires: ";
    strcat(reponse,*swap);
    strcat(reponse,date);
    memset(swap,0,sizeof (swap));

    *swap="Cache-Control: max-age=60\n"
          "Vary: Accept-Encoding\n"
          "Vary: Accept-Encoding\n"
          "X-Cache: \n"
          "Content-lenqth: 224 \n"
          "\n";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));
    strcat(reponse,http_response.location);

    strcat(reponse,http_response.body);

//    printf("aaaaaaaaaaaaaaa %s  \n",http_response.body);
    return  reponse;

}

char status_head[40]="HTTP/1.1 ";
char status_tail[]=" ok\n";// 这里有个未解问题 就是status在下面会被覆盖，它是在strcat之后被覆盖，
void set_status(char *__rps){
    if (__rps== nullptr) http_response.status="200";
        strcat(status_head,__rps);
        strcat(status_head,status_tail);
        http_response.status =status_head;


//    printf("%s\n",http_response.status);
}

void  set_header(char *__rps){
//    if (__rps== nullptr) http_response.status="HTTP/1.1 200 ok\n";
//    else  http_response.status=__rps;
}
char body_head[1024]={0};
char body_tail[] ="\n";
void set_body( char *__rps){

    if (__rps== nullptr) http_response.body="error!\n";

    strcat(body_head,body_tail);//正文空一行
    strcat(body_head,__rps);//正文内容
    http_response.body =body_head;
//    printf("现在正在打印body %s \n",http_response.body);
//    printf("%s\n",http_response.text);
}

char contentype_head[40]="Content-Type: ";
char conttentype_tail[]="\n";

void set_ContentType(char *__rps){
    if (__rps== nullptr) http_response.ContentType="text/html;charset=UTF-8";

    strcat(contentype_head,__rps);
    strcat(contentype_head,conttentype_tail);
   http_response.ContentType=contentype_head;

//    printf("1");
//    printf("%s\n",http_response.ContentType);
//    printf("%s\n",http_response.status);
//    printf("%s\n",http_response.text);

}

char cookie_head[1024]="Cookie: ";
char cookie_tail[]="\n";
void set_cookie( char *__rps){
    strcat(cookie_head,__rps);
    strcat(cookie_head,cookie_tail);
    http_response.cookie=cookie_head;
}
char location_head[1024]="Location: ";
char location_tail[]="\n";
void set_location( char *__rps){

    strcat(location_head,__rps);
    strcat(location_head,location_tail);
    http_response.location=location_head;

}
void  do_init(){

    http_response.ContentType="Content-Type:text/html;charset=UTF-8 \n";
    http_response.status="HTTP/1.1 200 ok \n";
}
void do_clear(){
    printf("已经清空\n");
    http_response.status= nullptr;
    http_response.ContentType= nullptr;
    http_response.body= nullptr;
    http_response.cookie= nullptr;
    http_response.header= nullptr;
    http_response.location= nullptr;
    memset(body_head,0,sizeof (body_head));
}