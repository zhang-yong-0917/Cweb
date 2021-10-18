//
// Created by zy on 2021/8/4.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <cstring>
#include <cstdio>
#include <arpa/inet.h>
#include <unistd.h>

int redis(){
    int   sockfd, n;
    char  recvline[4096], sendline[4096];
    struct sockaddr_in  servaddr;
//Type就是socket的类型，对于AF_INET协议族而言有流套接字(SOCK_STREAM)、数据包套接字(SOCK_DGRAM)、原始套接字(SOCK_RAW)
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6379);
    //inet_pton是一个IP地址转换函数，
    // 可以在将IP地址在“点分十进制”和“二进制整数”之间转换而且，
    // inet_pton和inet_ntop这2个函数能够处理ipv4和ipv6。
    if( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
        printf("inet_pton error for 127.0.0.1");
        return 0;
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    printf("send msg to server: \n");
    fgets(sendline, 4096, stdin);//相当于java的Scanner
    if( send(sockfd, sendline, strlen(sendline), 0) < 0){
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        return 0;
    }
    close(sockfd);
    return 0;

}
//int main(){
//    client1();
//    return 0;
//}