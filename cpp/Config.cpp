////
//// Created by zy on 2021/8/22.
////
//
//#include <cstdio>
//#include <cstring>
//#include "Config.h"
//#define  configPath "/home/zy/桌面/config.txt"
//
//
//int config(){
//
//}
////int fprintf_buf(char *buf)
////{
////    FILE *fb= fopen(configPath,"r");
////    if(fb == NULL)
////    {
////        printf("open error B!\n");
////        return 0;
////    }
////    fprintf(fb," %s\n",buf);
////    fclose(fb);
////
////    return 0;
////}
//char *fscanf( ){
//    char configmsg[100]={0};
//    FILE *fp= fopen(configPath,"r");;
//    if(fp == NULL)
//    {
//        printf("open error C!\n");
//        return 0;
//    }
//
//    while(fgets(configmsg, 100, fp) != NULL)
//    {
////        memcpy(msg,finall,sizeof(msg));
//        strcat(finall, configmsg);
////        p.rintf("%s",msg);
//    }
//    fclose(fp);
//    return finall;
//}