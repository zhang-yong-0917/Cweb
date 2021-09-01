#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "time.h"
#include "../head_h/Time.h"
//
// Created by zy on 2021/8/18.
//
char reponse[1024]={0};

int Spell(char* reponse);

char * ResponseSpell(char* buf){
    memset(reponse,0,sizeof (reponse));
    Spell(reponse);
    strcat(reponse,buf);
    return reponse;
}

int Spell(char* reponse){
    char* swap[1024]={0};
    char date[100]={0};
    *swap="HTTP/1.1 200 ok\n";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));

    TimeFile(date);
    *swap="Date: ";
    strcat(reponse,*swap);
    strcat(reponse,date);

    *swap="Content-Type: text/html;charset=UTF-8\n"
          "Connection: keep-alive\n"
          "Server: squid/3.5.24\n"
          "vary:Accept-Encoding";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));

    *swap="Expires: ";
    strcat(reponse,*swap);
    strcat(reponse,date);
    memset(swap,0,sizeof (swap));

    *swap="Cache-Control: max-age=60\n"
          "Vary: Accept-Encoding\n"
          "Vary: Accept-Encoding\n"
          "X-Cache: \n"
          "Content-lenqth: 224 \n"
          "\n";
    strcat(reponse,*swap);
    memset(swap,0,sizeof (swap));
}