#include <cstring>
#include "stdio.h"
#include "../../head_h/do_servlet.h"
#include "../../head_h/Analyse.h"

struct s_servlet response;

int response_body(char* body);
int response_content_type(char* contenttype);
int response_status(char* sc);
int response_cookie(char* k,char*v);
int response_cookie_path(char* path);
int response_cookie_maxage(char* maxtime);
int response_location(char *location);
int cookie_tail_all(char* cookie);
int cookie_end();
/////////////////////////////
char* request_cookies();
char* request_method();
char* request_accept();
char* request_parameter();
char* request_addr();
char* request_port();
char* request_host();
char* request_protocol();
char* request_session_id();
char* request_session();
char* requset_url();
char* request_dispatcher();
//////////////////////////////////////////////////////RESPONSE
//BODY
int  response_body(char* body){
    char swap[10240]={0};
    char* a=" \n";
    strcat(swap,a);
    strcat(swap,body);
    response.httpresponse.body=swap;
    sevlet_response(&response,RESPONSE_BODY);

}
//CONTENT TYPE
int response_content_type(char* content_type){
    char swap[1024]={0};
    char* a="Content-Type:";
    strcat(swap,a);
    strcat(swap,content_type);
    strcat(swap,"\n");

    response.httpresponse.ContentType=swap;
    sevlet_response(&response,RESPONSE_CONTENTTYPE);
//    printf("%s\n",swap);
}
//STATUS
int response_status(char* sc){
    char swap[1024]={0};
    char* a="HTTP/1.1 ";
    strcat(swap,a);
    strcat(swap,sc);
    strcat(swap," OK \n");

    response.httpresponse.status=swap;
    sevlet_response(&response,RESPONSE_STATUS);
//    printf("%s\n",swap);
}
//LOCATION
int response_location(char *location){

    char swap[1024]={0};
    char* a="Location: ";
    strcat(swap,a);
    strcat(swap,location);
    strcat(swap,"\n");

    response.httpresponse.location=swap;
    sevlet_response(&response,RESPONSE_LOCATION);
//    printf("%s\n",swap);
}
//COOKIE
char cookie[4056]={0};
int response_cookie(char* k,char*v){

    char* a="set-Cookie:";
    strcat(cookie,a);

    strcat(cookie,k);
    strcat(cookie,"=");
    strcat(cookie,v);
    strcat(cookie,";");
//    printf("%s\n",swap);
}//注意cookie得保证name和value在前面，不然cookie_path在前面会认为其是cookie，只要前面不乱，后面的其他参数乱也没问题。例如：set-Cookie:testCookie=book;Path=/xxxxx; Expires=Thu, 01-Jan-1970 00:00:10 GMT; Domain=.zhangsan.com\n"


char swap[3072]={0};
int cookie_tail_all(char* cookie){
        strcat(swap,cookie);
}//保证除了name和value，其余参数的位置正确

int cookie_end(){

    strcat(cookie,swap);
    strcat(cookie,"\n");

    response.httpresponse.cookie=cookie;
    sevlet_response(&response,RESPONSE_COOKIE);

    memset(cookie,0,sizeof (cookie));
    memset(swap,0, sizeof(swap));//清除缓存

//    printf("b:%s\n",cookie);
}

int response_cookie_path(char* path){
    char swap[1024]={0};
    char* a="Path=";

    strcat(swap,a);
    strcat(swap,path);
    strcat(swap,";");
    cookie_tail_all(swap);
//    printf("%s\n",swap);
}

int response_cookie_maxage(char* maxtime){
    char swap[1024]={0};
    char* a=" Max-Age=";
    strcat(swap,a);
    strcat(swap,maxtime);
    strcat(swap,";");
    cookie_tail_all(swap);
//        printf("%s\n",swap);
}
int response_cookie_domain(char* domain ){
    char swap[1024]={0};
    char* a=" Domain=";
    strcat(swap,a);
    strcat(swap,domain);
    strcat(swap,";");
    cookie_tail_all(swap);
//            printf("%s\n",swap);
}


//////////////////////////////////////////////////////Request
struct request request_src;

char* request_save(request* request){
request_src=*request;

}
//获取所有的cookie,存在数组里面
char* request_cookies(){

}
//返回请求使用的http的方法，如：get，post，put等
char* request_method(){
    return request_src.method;
}
//获取Accept里面的内容，包含：text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,
char* request_accept(){
    return request_src.accept;
}
//接收页面提交的 参数，主要有表单提交的参数、URL重写传递的参数（http://item.jsp?id=1中的id值）等
char* request_parameter(){
    return request_src.parament;
}
//获取发送请求着的ip地址，如：127.0.0.1
char* request_addr(){
    return request_src.addr;
}

//获取发送请求者的端口号，如：8080
char* request_port(){
    return request_src.port;
}

//获取发送请求者的主机名称：Host: localhost:8080
char* request_host(){
    return request_src.host;
}

//获取这个请求所用的协议，如HTTP/1.1
char* request_protocol(){
    return request_src.protocol;
}

//返回这个请求对应的SessionId
char* request_session_id(){

}
//返回这个请求相关联的session，如果没有相应的session，那么会新建一个
char* request_session(){

}
//返回请求的url中的资源部分，如:一个请求通过 /catalog/books?id=1这样的URL路径访问，这个方法将返回/catalog/books。
char* requset_url(){
    return request_src.url;
}
