//
// Created by zy on 2021/10/26.
//

#include <cstring>
#include "../head_h/MyController.h"
#include "../head_h/Analyse.h"
#include "../head_h/ReadHtml.h"
#include "../head_h/servlet.h"

//////////////////////////request_strcmp
int request_strcmp(char* str1,char*str2){
    while(*str1 && (*str1==*str2)){
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}
//////////////////////////////filter
char* filter(char* dest,char * swap){
//    || dest[s]==' '|| dest[s]==':'
    int dest_len= strlen(dest);

    for (int s = 0; s < dest_len; ++s) {
        if (dest[s]=='\r'||dest[s]=='\n'){
            continue;
        }
        swap[s]=dest[s];
    }
    return swap;
}
////////////////////////////method
char* analyse_request_method(char* k, request *v, char* request, int request_len, char* filter_method){
    char swap_method[10]={0};//存放value的数组

    if(strcmp(k,"Method")==0){
        for (int i = 0; i < request_len; ++i) {
            if (request[i]==' ')  {
                strncpy(swap_method, request, i);
                break;
            }
        }

        v->method=filter(swap_method,filter_method);//过滤一些其他东西
        printf("method: %s \n",v->method);
        return v->method ;
    }
    printf("method 解析失败\n");
}
/////////////////////////////url
char* analyse_request_url(char* k, request *v, char* request, int request_len, char* filter_url){
    char swap_url[request_len]={0};//存放value的数组
//    char filter_method[request_len]={0};//用于后面filter时候交换用的数组

    if(strcmp(k,"Url")==0){
        for (int i = 0; i < request_len; ++i) {
            if (request[i]=='/')//从 /开始解析
            {
                for (int j = 0; j < (request_len-i); ++j) {
                    if (request[i+j]==' ')// 到空格结束
                    {
                        break;
                    }
                    if(request[i + j]==' ' || request[i + j]==':') {
                        continue;
                    }
                    swap_url[j]=request[i + j];
                }
                break;
            }
        }
    }else{
        return v->url= nullptr;
        printf("url解析失败\n");
    }

    v->url= filter(swap_url,filter_url);
    printf("url: %s \n",v->url);
    return v->url;
}
//////////////propotol
char* analyse_request_protocol(char* k, request *v, char* request, int request_len, char* filter_protocol){

    char swap_protocol[15]={0};//存放value的数组
    int flag=-1;
        for (int i = 0; i < request_len; ++i) {
            if (request[i]==' ')//从 第二次 空格 开始解析
            {
                flag+=1;
                if (flag==1){
                    for (int j = 0; j < (request_len-i); ++j) {
                        if (request[i+j]=='\n')// 到\n结束
                        {
                            break;
                        }
                        swap_protocol[j]=request[i + j];
                    }
                    break;
                }
            }
        }

        v->protocol= filter(swap_protocol,filter_protocol);
        printf("propotol: %s \n",v->protocol);

        return v->protocol;

}
///////////////////addr
char* analyse_request_addr(char* k, request *v, char* request, int request_len, char* filter_addr){
    char swap_addr[25]={0};//存放value的数组

    for (int move = 0; move < request_len; ++move) {
        if (request[move] == '\n'){
            if (request[move + 1] == 'H'){
                request= request + move + 1;
                request_len= request_len - move - 1;
                break;
            }
        }//将指针移动到host这一行
    }

    if(strcmp(k,"Addr")==0){

        for (int i = 0; i < request_len; ++i) {

            if (request[i]==' ')//从 空格开始解析
            {
                for (int j = 0; j < (request_len-i); ++j) {
                    if (request[i+j]==':')// 到:结束
                    {
                        break;
                    }
                    swap_addr[j]=request[i + j];
                }
                break;
            }
        }
    }else{
        printf("addr解析失败");
        return v->addr= nullptr;
    }
    v->addr= filter(swap_addr,filter_addr);
    printf("addr: %s \n",v->addr);
    return v->addr;
}
//////////////port
char* analyse_request_port(char* k, request *v, char* request, int request_len, char* filter_port ){
    char swap_port[10]={0};//存放value的数组

    int flag=-1;
    if(strcmp(k,"Port")==0){
        for (int i = 0; i < request_len; ++i) {
            if (request[i]==':')//从 第二次 ：开始解析
            {
                flag+=1;
                if (flag==1){
                    ++i;
                    for (int j = 0; j < (request_len-i); ++j) {
                        if (request[i+j]=='\n')// 到\n结束
                        {
                            break;
                        }

                        swap_port[j]=request[i+j];
                    }
                    break;
                }
            }
        }
    }else{
        printf("port解析失败");
        return v->port= nullptr;

    }
    v->port= filter(swap_port,filter_port);
    printf("port: %s \n",v->port);
    return v->port;
}



char* analyse_request_parament(char* k, request *v, char* request, int request_len){

}


char* anlyse_request_host(char* k, request *v, char* request, int request_len, char* filter_host){
    char swap_total[request_len]={0};//存放value的数组


    int k_len= strlen(k);//获取k的长度
    char k_tow[k_len]={0};//从request中解析出来的k'将于k进行比较是否相同
    int flag=-1;
    int j = 0;

    for (int i = 0; i < request_len; ++i) {
        if (request[i]=='\n'){

            if (k[0]==request[i+1]){

                for (; j < k_len; ++j) {
                    k_tow[j]=request[i+1+j];
                }//获取k‘

                flag= request_strcmp(k,k_tow);//相等 为0,
                if (flag==0){
                    request=request+i+j+1;//移动到当前 想要获取到的行位置
                    request_len=request_len-i-j-1;
//                    printf("移动到的位置：%s\n",request_src);
                    break;

                } else{
                    j=0;
                    continue;
                }
            }else continue;
        }
    }

    for (int t = 0; t < request_len; ++t) {
                    if (request[t]==' ')//从 空格 开始解析
            {
//                        ++t;
                for (int j = 0; j < (request_len-t); ++j) {
                        if (request[t+j]=='\n')// 到\n结束
                        {
                            break;
                        }
                    swap_total[j]=request[t + j];
                }
                break;
            }
    }


        v->host=filter(swap_total,filter_host);
        printf("Host: %s \n",v->host);
        return v->host;

}
char* anlyse_request_accept(char* k, request *v, char* request, int request_len, char* filter_accept){
    char swap_total[request_len]={0};//存放value的数组


    int k_len= strlen(k);//获取k的长度
    char k_tow[k_len]={0};//从request中解析出来的k'将于k进行比较是否相同
    int flag=-1;
    int j = 0;

    for (int i = 0; i < request_len; ++i) {
        if (request[i]=='\n'){

            if (k[0]==request[i+1]){

                for (; j < k_len; ++j) {
                    k_tow[j]=request[i+1+j];
                }//获取k‘

                flag= request_strcmp(k,k_tow);//相等 为0,
                if (flag==0){
                    request=request+i+j+1;//移动到当前 想要获取到的行位置
                    request_len=request_len-i-j-1;
//                    printf("移动到的位置：%s\n",request_src);
                    break;

                } else{
                    j=0;
                    continue;
                }
            }else continue;
        }
    }

    for (int t = 0; t < request_len; ++t) {
        if (request[t]==' ')//从 空格 开始解析
        {
//                        ++t;
            for (int j = 0; j < (request_len-t); ++j) {
                if (request[t+j]=='\n')// 到\n结束
                {
                    break;
                }
                swap_total[j]=request[t + j];
            }
            break;
        }
    }


        v->accept= filter(swap_total,filter_accept);
        printf("Accept: %s \n",v->accept);
        return v->accept;
}
char* anlyse_request_accept_encoding(char* k, request *v, char* request, int request_len, char* filter_accept_encoding){
    char swap_total[request_len]={0};//存放value的数组
//    char filter_method[request_len]={0};//用于filter交换时的数组

    int k_len= strlen(k);//获取k的长度
    char k_tow[k_len]={0};//从request中解析出来的k'将于k进行比较是否相同
    int flag=-1;
    int j = 0;

    for (int i = 0; i < request_len; ++i) {
        if (request[i]=='\n'){

            if (k[0]==request[i+1]){

                for (; j < k_len; ++j) {
                    k_tow[j]=request[i+1+j];
                }//获取k‘

                flag= request_strcmp(k,k_tow);//相等 为0,
                if (flag==0){
                    request=request+i+j+1;//移动到当前 想要获取到的行位置
                    request_len=request_len-i-j-1;
//                    printf("移动到的位置：%s\n",request_src);
                    break;

                } else{
                    j=0;
                    continue;
                }
            }else continue;
        }
    }

    for (int t = 0; t < request_len; ++t) {
        if (request[t]==' ')//从 空格 开始解析
        {
//                        ++t;
            for (int j = 0; j < (request_len-t); ++j) {
                if (request[t+j]=='\n')// 到\n结束
                {
                    break;
                }
                swap_total[j]=request[t + j];
            }
            break;
        }
    }

        v->accept_encoding=filter(swap_total,filter_accept_encoding);
        printf("Accept-Encoding: %s \n",v->accept_encoding);
        return v->accept_encoding;
}
char* anlyse_request_accept_language(char* k, request *v, char* request, int request_len, char* filter_accept_language) {
    char swap_total[request_len] = {0};//存放value的数组
//    char filter_method[request_len] = {0};//用于filter交换时的数组

    int k_len = strlen(k);//获取k的长度
    char k_tow[k_len] = {0};//从request中解析出来的k'将于k进行比较是否相同
    int flag = -1;
    int j = 0;

    for (int i = 0; i < request_len; ++i) {
        if (request[i] == '\n') {

            if (k[0] == request[i + 1]) {

                for (; j < k_len; ++j) {
                    k_tow[j] = request[i + 1 + j];
                }//获取k‘

                flag = request_strcmp(k, k_tow);//相等 为0,
                if (flag == 0) {
                    request = request + i + j + 1;//移动到当前 想要获取到的行位置
                    request_len = request_len - i - j - 1;
//                    printf("移动到的位置：%s\n",request_src);
                    break;

                } else {
                    j = 0;
                    continue;
                }
            } else continue;
        }
    }

    for (int t = 0; t < request_len; ++t) {
        if (request[t] == ' ')//从 空格 开始解析
        {
//                        ++t;
            for (int j = 0; j < (request_len - t); ++j) {
                if (request[t + j] == '\n')// 到\n结束
                {
                    break;
                }
                swap_total[j] = request[t + j];
            }
            break;
        }
    }

        v->accept_language = filter(swap_total, filter_accept_language);
        printf("Accept-Language： %s \n", v->accept_language);
        return v->accept_language;

}
char* anlyse_request_cookie(char* k, request *v, char* request, int request_len, char* filter_cookie){
    char swap_total[request_len]={0};//存放value的数组
//    char filter_method[request_len]={0};//用于filter交换时的数组

    int k_len= strlen(k);//获取k的长度
    char k_tow[k_len]={0};//从request中解析出来的k'将于k进行比较是否相同
    int flag=-1;
    int j = 0;

    for (int i = 0; i < request_len; ++i) {
        if (request[i]=='\n'){

            if (k[0]==request[i+1]){

                for (; j < k_len; ++j) {
                    k_tow[j]=request[i+1+j];
                }//获取k‘

                flag= request_strcmp(k,k_tow);//相等 为0,
                if (flag==0){
                    request=request+i+j+1;//移动到当前 想要获取到的行位置
                    request_len=request_len-i-j-1;
//                    printf("移动到的位置：%s\n",request_src);
                    break;

                } else{
                    j=0;
                    continue;
                }
            }else continue;
        }
    }

    for (int t = 0; t < request_len; ++t) {
        if (request[t]==' ')//从 空格 开始解析
        {
//                        ++t;
            for (int j = 0; j < (request_len-t); ++j) {
                if (request[t+j]=='\n')// 到\n结束
                {
                    break;
                }
                swap_total[j]=request[t + j];
            }
            break;
        }
    }

        v->cookie=filter(swap_total,filter_cookie);
        printf("Cookie： %s \n",v->cookie);
        return v->cookie;
}

void Analyse_two(request *v) {
    request_save(v);//将该request结构体指向传过去的
    doRequestMapping(v->url);
    path(v->url);

//    char rex[1024]={0};
//    int status;
//    int cflags=REG_EXTENDED;
//    regmatch_t pmatch[1];
//    const size_t nmatch=1;
//    regex_t  reg;
//
//    const char* pattern="(/\\w*){0,}/(\\w*)(.html)|(/\\w*)(.html)|( / ){1}";
//    //编译正则模式
//    regcomp(&reg,pattern,cflags);
//
//    //执行正则表达式和缓存的比较
//    status= regexec(&reg,buf,nmatch,pmatch,0);
//    //打印匹配的字符串
//    if (status == REG_NOMATCH) printf("No Match\n");
//    else if(status == 0) {
//        printf("Match:\n");
//        int t=0;
//
//        for (int i = pmatch[0].rm_so; i <pmatch[0].rm_eo ; ++i){
//            if (buf[i]==' '){
//                ++t;
//            } else{
//                putchar(buf[i]);
//                rex[t]=buf[i];
//                ++t;
//            }
//        }
////        printf("url%s",rex);
//        printf("\n");
//    path(a.url);

//    doRequestMapping(request_src.url);
//
//    }
//    regfree(&reg);
//    return 0;
}
