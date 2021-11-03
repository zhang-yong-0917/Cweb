#include "Analyse.h"

#ifndef JIEXI_SERVLET_H
#define JIEXI_SERVLET_H

#endif //JIEXI_SERVLET_H

int response_body(char* body);
int response_content_type(char* content_type);
int response_status(char* sc);
int response_cookie(char* k,char*v);

int response_cookie_path(char* path);

int response_cookie_maxage(char* maxtime);
int response_cookie_domain(char* domain );
int response_location(char *location);
int cookie_end();
////////////////////////
char* request_save(request* request);
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
