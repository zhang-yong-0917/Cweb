#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "time.h"
#include "../head_h/Time.h"
#include "../head_h/do_servlet.h"
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
void  do_init();
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
    printf("response: %s\n",http_response.status);
    strcat(reponse,http_response.status); //设置响应头
    //当没用任何人调用时候为空指针异常

    TimeFile(date);//获取时间
//    *swap="Date: ";
//    strcat(reponse,*swap);
    strcat(reponse,date);

    printf("response: %s\n",http_response.ContentType);
    strcat(reponse,http_response.ContentType);

    printf("response: %s\n",http_response.location);
    strcat(reponse,http_response.location);

    printf("response: %s\n",http_response.cookie);
    strcat(reponse,http_response.cookie);

//    "Content-Type: text/html;charset=UTF-8\n"
    *swap="Connection: keep-alive  \n"
          "Server: squid/3.5.24\n"
          "set-Cookie:testCookie=book;Path=/xxxxx; Expires=Thu, 01-Jan-1970 00:00:10 GMT; Domain=.zhangsan.com\n"
          "vary:Accept-Encoding";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));

    *swap="Expires: ";
//    strcat(reponse,*swap);
    strcat(reponse,date);
    memset(swap,0,sizeof (swap));

    *swap="Cache-Control: no-cache\n"
          "Vary: Accept-Encoding\n"
          "Vary: Accept-Encoding\n"
          "X-Cache: \n"
          "Content-lenqth: 224 \n"
          "\n";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));

    strcat(reponse,http_response.body);

//    printf("response: %s  \n",http_response.body);
    return  reponse;

}

char status_head[40];
char status_tail[]=" ok\n";// 这里有个未解问题 就是status在下面会被覆盖，它是在strcat之后被覆盖，
void set_status(char *__rps){
    strcat(status_head,__rps);

    http_response.status= nullptr;//清除初始化的值，因为找不到可以直接覆盖的方法所以出此下策。
    http_response.status =status_head;
}


void  set_header(char *__rps){
    if (__rps== nullptr) __rps="";
    else  http_response.status=__rps;
}

char body_head[10240];
void set_body( char *__rps){
    strcat(body_head,__rps);//正文内容

    http_response.body= nullptr;
    http_response.body =body_head;
}

char contentype_head[40];
void set_ContentType(char *__rps){
    strcat(contentype_head,__rps);

    http_response.ContentType= nullptr;
   http_response.ContentType=contentype_head;



}

char cookie_head[1024];
void set_cookie( char *__rps){
    strcat(cookie_head,__rps);

    http_response.cookie= nullptr;
    http_response.cookie=cookie_head;
}

char location_head[1024];
void set_location( char *__rps){
    strcat(location_head,__rps);

    http_response.location= nullptr;
    http_response.location=location_head;

}
void  do_init(){

    http_response.ContentType="Content-Type:text/html;charset=UTF-8 \n";
    http_response.status="HTTP/1.1 200 ok \n";
    http_response.location=" \n";
    http_response.cookie=" \n";
    http_response.body=" 404 寻找不到资源！\n";
    http_response.header=" \n";

}
void do_clear(){

    http_response.status= nullptr;
    http_response.ContentType= nullptr;
    http_response.body= nullptr;
    http_response.cookie= nullptr;
    http_response.header= nullptr;
    http_response.location= nullptr;

    memset(body_head,0,sizeof (body_head));
    memset(status_head,0, sizeof(status_head));
    memset(location_head,0, sizeof(location_head));
    memset(cookie_head,0, sizeof(cookie_head));
    memset(contentype_head,0, sizeof(contentype_head));

    do_init();
    printf("已经清空\n");
}