#include <iostream>
#include <cstring>
#include "../head_h/Analyse.h"
#include "../head_h/Socket.h"
#include "../head_h/threadpool.h"
#include <stdio.h>
#include "../head_h/servlet.h"
#include "../head_h/MyController.h"
//void *func(void * arg){
//    char *a= (char*)arg;
//    printf("thread %s\n",a);
//    return NULL;
//}
int a() {
    printf("sahuodalkd\n");
}
int c(){
    printf("sauihduiagyud%s\n",requset_url());
}
int main() {
    RequestMapping("/login", reinterpret_cast<void *(*)(void *)>(a), NULL);
    RequestMapping("/aaa", reinterpret_cast<void *(*)(void *)>(c), NULL);

    serverepoll();
//    char a[]="http://127.0.0.1:8080/index.jsp";
//    URL(a);
//    Analyse();
//char* a="/home/zy/桌面/Test.html";
//    open(a, nullptr, nullptr);

//    redis();
//    response_cookie_maxage("20");
//    response_cookie("zhansgan","sdasd");
//    response_cookie_path("/a/b/c/d");
//    response_cookie_domain("./aioofjao");
//
//    response_location("http:localhost:8080/asdadx");
//    response_status("200");
//    response_content_type("text/html;charset=UTF-8");
//    response_body("adahsdkajvbdaiusoajio");
//    cookie_end();





    printf("aa %s\n",request_method());
    printf("aa %s\n",request_accept());
    printf("aa %s\n",request_addr());
    printf("aa %s\n",request_port());
    printf("aa %s\n",request_host());
    printf("aa %s\n",request_protocol());
    printf("aa %s\n",requset_url());


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
