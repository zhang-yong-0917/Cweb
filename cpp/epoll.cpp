//
// Created by zy on 2021/8/16.
//

#include <sys/epoll.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../head_h/File.h"
#include "../head_h/Analyse.h"
#include "../head_h/Reponsehttp.h"

#define FDSIZE        1024
#define EPOLLEVENTS 20
#define MAXSIZE     1024

void add_event(int epollfd,int fd,int state);
void delete_event(int epollfd,int fd,int state);
void modify_event(int epollfd,int fd,int state);

/*IO多路复用epoll*/
void do_epoll(int listenfd);
/*事件处理函数*/
void handle_eventsserver(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf);
/*处理接收到的连接*/
void handle_accpet(int epollfd, int listenfd, char *string);
/*读处理*/
void do_readserver(int epollfd,int fd,char *buf);
/*写处理*/
void do_writeserver(int epollfd,int fd,char *buf);

char buf    [MAXSIZE];
void do_epoll(int listenfd){
    int epollfd;
    struct epoll_event events[EPOLLEVENTS];
    int ret;

    memset(buf,0,MAXSIZE);
    /*创建一个描述符*/
    epollfd = epoll_create(FDSIZE);//该函数生成一个epoll专用的文件描述符，其中的参数是指定生成描述符的最大范围
    /*添加监听描述符事件*/
    add_event(epollfd,listenfd,EPOLLIN);
    while(1){
        /*获取已经准备好的描述符事件*/
        ret = epoll_wait(epollfd,events,EPOLLEVENTS,-1);//该函数用于轮询i/O事件的发生。参数：epfd：有epoll_create生成的epoll专用的文件描述符；epoll_event：用于回传代处理事件的数组；maxevents：每次能处理事件数；timeout：等待i/o事件发生的超时值。
        if(ret == -1){
            perror("epoll_wait");
            close(listenfd);
            break;
        }
//        printf("afterlaiguo：%s\n",buf);
        handle_eventsserver(epollfd,events,ret,listenfd,buf);//重点注意这个ret，它返回的是已经有事儿的fd的个数
//        printf("beforlaiguo：%s\n",buf);
        //这样一会儿轮循的就不是所有的fd了
    }
    close(epollfd);
}

void handle_eventsserver(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf){
    int i;
    int fd;
    /*进行选好遍历*/
//     printf("A%s\n",buf);
    for (i = 0;i < num;i++){
//        printf("i:%d\n",i);
//        printf("num:%d\n",num);
        fd = events[i].data.fd;//event数组里面的fd和当前的sockedfd是否相同；
        /*根据描述符的类型和事件类型进行处理*/
        if ((fd == listenfd) &&(events[i].events & EPOLLIN)){
            printf("afterhandle:%s\n",buf);
            handle_accpet(epollfd, listenfd, buf);
            printf("beforhandle:%s\n",buf);
        }
        else if (events[i].events & EPOLLIN){
            printf("afterread:%s\n",buf);
            do_readserver(epollfd,fd,buf);
            printf("beforread:%s\n",buf);
        }

        else if (events[i].events & EPOLLOUT){
            printf("afterwrite:%s\n",buf);
            do_writeserver(epollfd,fd,buf);
            printf("beforwrite:%s\n",buf);
        }

    }
}

void handle_accpet(int epollfd,int listenfd,char *buf){
    int clifd;
    struct sockaddr_in cliaddr;
    socklen_t  cliaddrlen=sizeof(cliaddr);
    clifd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddrlen);
//    printf("C%s\n",buf);
    if (clifd == -1){
        close(listenfd);
        perror("accpet error:");
    }
    else{
        printf("=====================================================\n");
        printf("accept a new client: %s:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
        fprintf_port(inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
//        Analyse();
        /*添加一个客户描述符和事件*/
        add_event(epollfd,clifd,EPOLLIN);
    }
}

void do_readserver(int epollfd,int fd,char *buf){
    int nread;
    nread = read(fd,buf,MAXSIZE);//这里buf才会有东西，上面都没有

//    printf("ahfnlks%s\n",buf);
    if (nread == -1){
        perror("read error:");
        close(fd);
        delete_event(epollfd,fd,EPOLLIN);
    }
    else if (nread == 0){
//        fprintf(stdin,"client close.\n");//?????????????????????stderr
        close(fd);
        delete_event(epollfd,fd,EPOLLIN);
        return;
    }
    else {
        if (filterFacicon(buf)==0){
            //因为浏览器会自动发一次请求寻找/facicon.ico目录下的文件，所以这个判断会将这个请求拦截下来.
            memset(buf,0,MAXSIZE);
//            close(fd);
            delete_event(epollfd,fd,EPOLLIN);
        }else{
            fprintf_buf(buf);
//        URL(buf);
            Analyse_two(buf);//解析http路径
            printf("read messag3e is : %s",buf);
            /*修改描述符对应的事件，由读改为写*/
            modify_event(epollfd,fd,EPOLLOUT);
//        memset(buf,0,MAXSIZE);
        }
    }
}

void do_writeserver(int epollfd,int fd,char *buf){
    int nwrite;
    char *a=Reponsehttp(buf);
    printf("write messag3e is : %s",a);
    char *b=ResponseSpell(a);
    printf("write messag3e is : %s",b);
    nwrite = write(fd,b,strlen(b));
    if (nwrite == -1){
        perror("write error:");
        close(fd);
        delete_event(epollfd,fd,EPOLLOUT);
    }
    else
        modify_event(epollfd,fd,EPOLLIN);
        memset(buf,0,MAXSIZE);
}
void add_event(int epollfd, int fd, int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;//也就是sockedfd
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);//epfd:由epoll_create生成的epoll专用的文件描述符;
    //op:要进行的操作，可能的取值EPOLL_CTL_ADD注册、EPOLL_CTL_MOD修EPOLL_CTL_DEL删除;
    //fd:关联的文件描述符;
    // event:指向epoll_event的指针;
    //调用成功返回0,不成功返回-1；
}

void delete_event(int epollfd,int fd,int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);//该函数用于控制某个文件描述符上的事件，可以注册事件，修改，删除。成功返回0,不成功-1
}

void modify_event(int epollfd,int fd,int state){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&ev);
}