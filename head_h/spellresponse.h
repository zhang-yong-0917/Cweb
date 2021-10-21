//
// Created by zy on 2021/9/29.
//

#ifndef JIEXI_SPELLRESPONSE_H
#define JIEXI_SPELLRESPONSE_H

#endif //JIEXI_SPELLRESPONSE_H
extern char* ResponseSpell(char* buf);
extern  char * do_spell(char *reponse);
extern void do_init();
extern void set_status(char* __rps);
extern void  set_header( char *__rps);
extern void set_body( char *__rps);
extern void set_ContentType(char *__rps);
extern void set_cookie(char *__rps);
extern  void set_location(char *__rps);
extern void do_clear();