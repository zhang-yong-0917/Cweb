//
// Created by zy on 2021/8/17.
//

#include <cstdio>
#include "../head_h/ReadHtml.h"
#include "../head_h/File.h"
#include <pthread.h>
#include <cstring>
#include "../head_h/Analyse.h"
#include "../head_h/MyAnalysisNew.h"
#include "../head_h/servlet.h"
/*/C_Tomcat*/
 char Path[]= "/home/zy/桌面";
pthread_rwlock_t rwlock_reponse;
char httpmsg_reponse[1024]={0};



int ResetPath()//将路径重置
{
    memset(Path,0,sizeof (Path));
    char a[]="/home/zy/桌面";
    strcpy(Path,a);
    printf("Reset%s\n",Path);
}
char *fscanf_Reponse(char *finall)//读取路径中的数据转换为字节流
{

//    int flag= strcmp(Path,"/home/zy/桌面/Test.html");
////    pthread_rwlock_rdlock(&rwlock_reponse);
////    printf("aaaa%s\n",Path);
//
//    if (!flag){
//        open(Path, nullptr, Path);
//    }

    FILE *fp_reponse= fopen(Path,"r");
    if(fp_reponse == NULL)
    {

        response_content_type("text/html;charset=UTF-8");
        response_status("404");
        response_body("该资源不存在");
        printf("该文件不存在!\n");
        return 0;
    }

    while(fgets(httpmsg_reponse, 1024, fp_reponse) != NULL)
    {
//        memcpy(msg,finall,sizeof(msg));
        strcat(finall, httpmsg_reponse);
//        p.rintf("%s",msg);
    }
    response_body(finall);//将读取到的html传下去，组成报文

    fclose(fp_reponse);
    ResetPath();
//    pthread_rwlock_unlock(&rwlock_reponse);
    return finall;

}


//过渡函数，主要给epoll调用，并且重置buf。
char* readhtml(char *buf)
{

    memset(buf,0,sizeof (buf));
//    fprintf_buf();
    return fscanf_Reponse(buf);

}

//将从http获得的url拼接到Path上
int path(char *path)
{
    ResetPath();
    strcat(Path,path);
    printf("bbbb%s\n",Path);
}
//int fprintf_buf()
//{
////    pthread_rwlock_wrlock(&rwlock);
//    FILE *f= fopen(Path,"a+");
//    if(f == NULL)
//    {
//        printf("open error!\n");
//        return 0;
//    }
//    char a[]="aaaaa";
//    fprintf(f," %s\n",a);
//    fclose(f);
////    pthread_rwlock_unlock(&rwlock);
//    return 0;
//}