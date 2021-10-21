//
// Created by zy on 2021/9/25.
//

#ifndef JIEXI_SERVLET_H
#define JIEXI_SERVLET_H

#endif //JIEXI_SERVLET_H
#define RESPONSE_STATUS 1
#define RESPONSE_HEADER 2
#define RESPONSE_BODY 3
#define RESPONSE_CONTENTTYPE 4
#define RESPONSE_COOKIE 5
#define RESPONSE_LOCATION 6

struct s_http_request{

};// request 的结构体

struct  s_http_response{
    char* status= nullptr;
    char * header= nullptr;
    char * body= nullptr;
    char * ContentType= nullptr;
    char *cookie= nullptr;
    char * location= nullptr;
};//response 的结构体

struct  s_servlet{
//    char * port;
    s_http_request  httprequest;
    s_http_response  httpresponse;
};

extern void sevlet_response( s_servlet *rps,int __op);//sevlet 的使用可以通过#define 定义的 参数 来选择你要对报文进行什么样的处理
extern void clrear();

extern void  init();
extern struct s_servlet * destroy();


