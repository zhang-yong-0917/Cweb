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
