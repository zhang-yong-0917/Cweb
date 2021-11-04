//
// Created by mikasa on 2021/10/20.
//

#ifndef UNTITLED3_MYCONTROLLER_H
#define UNTITLED3_MYCONTROLLER_H

#endif //UNTITLED3_MYCONTROLLER_H
#include "stdio.h"

typedef struct Servlet{
    char * value; //url映射的路径
    void *(*function)(void *); //url路径对应的函数
    va_list args; //函数的参数
    int argsnum; //参数的个数
    struct Servlet * next;
    struct Servlet * left;
    struct Servlet * right;
    int listsize; //函数链表长度 如果函数链表长度超过64则转b+树
}ServletMapping;
void RequestMapping(char * value,void *(*function)(void * ),...);
void doRequestMapping(char * value);