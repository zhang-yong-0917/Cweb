//
// Created by mikasa on 2021/10/20.
//

#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "strings.h"
#include "../head_h/MyController.h"

ServletMapping * servletHeading;
ServletMapping * servletIndex;
void RequestMapping(char * value,void *(*function)(void * ),...){
    if (servletHeading==NULL){
        servletHeading=(ServletMapping *)malloc(sizeof(ServletMapping));
        servletIndex=servletHeading;
        servletHeading->value=NULL;
        servletHeading->function=NULL;
        servletHeading->next=NULL;
        servletHeading->left=NULL;
        servletHeading->right=NULL;
        servletHeading->listsize=0;
    }
    ServletMapping * servlet=(ServletMapping *)malloc(sizeof(ServletMapping));
    servlet->value=value;
    servlet->function=function;
    va_start(servlet->args,function);
    if (servletHeading->listsize<=64){
        servletIndex->next=servlet;
        servletIndex=servlet;
        servletHeading->listsize++;
    } else {
        //这里可扩展为b+树
    }
}
void doRequestMapping(char * value){
    if (servletHeading->listsize<=64){
        ServletMapping * index=servletHeading->next;
        while (index!=NULL){
            if (!strcmp(index->value,value)){
                index->function(index->args);
                break;
            } else{
                index=index->next;
            }
        }
    } else {

    }
}
