//
// Created by zy on 2021/10/26.
//

#ifndef JIEXI_DO_ANALYSE_H
#define JIEXI_DO_ANALYSE_H

#endif //JIEXI_DO_ANALYSE_H
#define Method "Method"
#define  Url "Url"
#define  Protocol  "Protocol"
#define  Host   "Host"
#define Addr    "Addr"
#define  Port   "Port"
#define  Accept  "Accept"
#define Accept_Encoding "Accept-Encoding"
#define Accept_Language "Accept-Language"
#define Cookie  "Cookie"
#define Parament "Parament"

char* analyse_request_method(char* k, request *v, char* request, int request_len, char* filter_method);
char* analyse_request_url(char* k, request *v, char* request, int request_len, char* filter_url);
char* analyse_request_protocol(char* k, request *v, char* request, int request_len, char* filter_protocol);
char* analyse_request_addr(char* k, request *v, char* request, int request_len, char* filter_addr);
char* analyse_request_port(char* k, request *v, char* request, int request_len, char* filter_port);
char* analyse_request_parament(char* k, request *v, char* request, int request_len, char* filter_parament);
char* anlyse_request_cookie(char* k, request *v, char* request, int request_len, char* filter_cookie);
char* anlyse_request_host(char* k, request *v, char* request, int request_len, char* filter_host);
char* anlyse_request_accept(char* k, request *v, char* request, int request_len, char* filter_accept);
char* anlyse_request_accept_language(char* k, request *v, char* request, int request_len, char* filter_accept_language);
char* anlyse_request_accept_encoding(char* k, request *v, char* request, int request_len, char* filter_accept_encoding);
char* anlyse_request_total(char* k, request *v, char* request, int request_len, char* filter_method);
void Analyse_two(request *v);