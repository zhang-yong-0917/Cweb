//
// Created by zy on 2021/8/4.
//

#ifndef JIEXI_ANALYSE_H
#define JIEXI_ANALYSE_H


typedef struct attribute{
    char * key;
    void * value;
}Attribute;

typedef struct request{
    char* method= nullptr;
    char* cookie= nullptr;
    char* accept= nullptr;
    char* parament= nullptr;
    char* addr= nullptr;
    char* port= nullptr;
    char* host= nullptr;
    char* protocol= nullptr;
    char* url= nullptr;
    char* session= nullptr;
    char* session_id= nullptr;
    char* accept_encoding= nullptr;
    char* accept_language= nullptr;
    Attribute * attributes[20];
}Request;

extern  int  filterFacicon(char *buf);
extern  int Analyse();
//extern void Analyse_two(struct request_src request);
extern  int analyse_request(char* request_msg);

#endif //JIEXI_ANALYSE_H


//request报文
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