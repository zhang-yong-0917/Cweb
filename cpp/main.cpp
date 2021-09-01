#include <iostream>
#include <cstring>
#include "../head_h/Analyse.h"
#include "../head_h/Socket.h"
#include "../head_h/threadpool.h"
#include <stdio.h>

//void *func(void * arg){
//    char *a= (char*)arg;
//    printf("thread %s\n",a);
//    return NULL;
//}

int main() {
//    char a[]="http://127.0.0.1:8080/index.jsp";
//    URL(a);
//    Analyse();
//char* a="/home/zy/桌面/Test.html";
//    open(a, nullptr, nullptr);

    serverepoll();
//    /* 线程池初始化，其管理者线程及工作线程都会启动 */
//    threadpool_t *thp = threadpool_create(10, 100, 100);
//    printf("threadpool init ... ... \n");
//
//    char* arg=(char *)"aaa";
//    /* 接收到任务后添加 */
//    threadpool_add_task(thp, *func,(void*)arg);
//
//    // ... ...

    /* 销毁 */
//    threadpool_destroy(thp);

//    client1();
    return 0;


}
