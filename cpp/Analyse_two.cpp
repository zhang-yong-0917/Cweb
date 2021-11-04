//
// Created by zy on 2021/8/22.
//
//#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <cstring>
#include "../head_h/Analyse.h"
#include "../head_h/do_analyse.h"

struct request _request;

int analyse_request(char* request_msg){
    int request_len= strlen(request_msg);//请求报文长度

    char filter_method[10]={0};//存解析出来的method
    char filter_url[request_len]={0};//存解析出来的url
    char filter_protocol[15]={0};//存解析出来的protocol
    char filter_addr[25]={0};//存解析出来的addr
    char filter_port[10]={0};//存解析出来的port
    char filter_host[50]={0};//存解析出来的host
    char filter_accept[request_len]={0};//存解析出来的accept
    char filter_accept_encoding[30]={0};//存解析出来的accept_encoding
    char filter_accept_language[30]={0};//存解析出来的accept_language
    char filter_cookie[request_len]={0};//存解析出来的cookie

    analyse_request_method(Method, &_request, request_msg, request_len,filter_method);
    analyse_request_url(Url, &_request, request_msg, request_len,filter_url);
    analyse_request_protocol(Protocol, &_request, request_msg, request_len,filter_protocol);
    analyse_request_addr(Addr, &_request, request_msg, request_len,filter_addr);
    analyse_request_port(Port, &_request, request_msg, request_len,filter_port);

//     analyse_request_parament(,&_request,request_msg, request_len);

    anlyse_request_host(Host, &_request, request_msg, request_len,filter_host);
    anlyse_request_cookie(Cookie, &_request, request_msg, request_len,filter_cookie);
    anlyse_request_accept(Accept, &_request, request_msg, request_len,filter_accept);
    anlyse_request_accept_encoding(Accept_Encoding, &_request, request_msg, request_len,filter_accept_encoding);
    anlyse_request_accept_language(Accept_Language, &_request, request_msg, request_len,filter_accept_language);

    Analyse_two(&_request);
}
//
//char* do_analysse(char* request, struct request_src request_struct){
//
//
//}