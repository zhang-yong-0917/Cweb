//
// Created by zy on 2021/10/13.
//

#include "../../head_h/do_servlet.h"
//
// Created by zy on 2021/9/27.
//

#include <cstdlib>
#include "stdio.h"
#include "../../head_h/servlet.h"
//#include "../../head_h/do_servlet.h"
#include "../../head_h/spellresponse.h"

struct s_http_response shr;
int i=-1;
void rsp_status( s_servlet *__rps);
void  rsp_header( s_servlet *__rps);
void rsp_body( s_servlet *__rps);
void rsp_ContentType( s_servlet *__rps);
void rsp_cookie( s_servlet *__rps);
void rsp_location(s_servlet *__rps);
void sevlet_response(s_servlet *__rps,int __op){
    if(i==-1){
        do_init();
        i++;
    }
    switch (__op) {
        case 1:
            rsp_status(__rps); break;
        case 2:
            rsp_header(__rps); break;
        case 3:
            rsp_body(__rps);break;
        case 4:
            rsp_ContentType(__rps);break;
        case 5:
            rsp_cookie(__rps);break;
        case 6:
            rsp_location(__rps);break;
        default:
            printf("__op  error");
    }
}

void rsp_status( s_servlet *__rps){
    shr.status=__rps->httpresponse.status;
    set_status(shr.status);
}
void  rsp_header( s_servlet *__rps){
    shr.header=__rps->httpresponse.header;
    set_header(shr.header);
}
void rsp_body( s_servlet *__rps){
    shr.body=__rps->httpresponse.body;
    set_body(shr.body);
}
void rsp_ContentType( s_servlet *__rps){
    shr.ContentType=__rps->httpresponse.ContentType;
    set_ContentType(shr.ContentType);

}
void rsp_cookie( s_servlet *__rps){
    shr.cookie=__rps->httpresponse.cookie;
    set_cookie(shr.cookie);
}

void rsp_location(s_servlet *__rps){
    shr.location=__rps->httpresponse.location;
    set_status("302");
    set_location(shr.location);
}

void clrear(){
    i-=1;
    do_clear();
}
// void init(){
//        (s_servlet*) malloc(sizeof (s_servlet));
//    (s_http_response*) malloc(sizeof (s_http_response));
////    (s*) malloc(sizeof (s_servlet));
//}

struct s_servlet * destroy(){

}