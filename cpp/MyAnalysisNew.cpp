//
// Created by mikasa on 2021/8/9.
//
#include "stdlib.h"
#include "stdio.h"
#include "strings.h"
#include "string.h"
#include "../head_h/MyAnalysisNew.h"
#define Controller 1;
#define Context 2;
#define Define 3;
#define Val 4;
#define Operator 5;
#define Fin 13;
#define Operator_Equal 501
typedef struct StringList{
    char * array;
    struct StringList *next;
}Node;
typedef struct WordList{
    char * array;
    struct WordList *next;
    struct WordList *left;
    struct WordList * right;
    int type;
    char * msg;
}Word;
typedef struct Grammar{
    char * array;
    struct Grammar *left;
    struct Grammar *right;
    int type;
};
typedef struct Variable{
    char * key;
    char * value;
};
Variable * vareax[20];
int varindex=0;
char * eax[20];
int eaxindex=0;
char * operatoreax[10];
int operatoreaxindex=0;
StringList * headsl=(StringList *)malloc(sizeof(StringList));
WordList * headctl=(WordList *)malloc(sizeof(WordList));
Grammar * root=(Grammar *)malloc(sizeof(Grammar));
Grammar * roots[10];
int trees=0;
StringList * List[50];
WordList * Wlist[50];
int listlen=0;
int wlistlen=0;
void bodydeal(FILE * fp);
void docon(WordList * segment);
void doval(WordList * segment);
void createoperatertree(Grammar * tree);
int operatortype=0;
int istrue=0;
char * thisfilepath=(char *)malloc(128);
char * thisuri=(char *)malloc(32);
char * thispath=(char *)malloc(96);
char temphtml[11]="Temp.html\0";
void replacehtml(char * context);
void replacehtml(char * array){
        FILE *fpSrc=NULL;
            FILE *fpDst=NULL;
            if ((fpSrc=fopen(thisfilepath,"r"))==NULL){
                perror("file open fail");
                exit(1);
            }
            int len=strlen(thispath);
            char temp[128];
            int i=0;
            for (int j=0; i < len+10; ++i) {
                if (i>len){
                    temp[i-1]=temphtml[j++];
                    continue;
                }
                temp[i]=thispath[i];
            }
            temp[i-1]='\0';
            printf("%s\n",temp);
            if ((fpDst=fopen(temp,"w"))==NULL)
            {
                perror("error!!!");
                exit(0);
            }
            char context[101];
            int atbody=0;
            while (fgets(context,sizeof(context),fpSrc)){
                if (!strcmp(context,"<body>\n")){
                    fputs(context,fpDst);
                    fputs(array,fpDst);
                    atbody=1;
                    continue;
                }
                if (atbody){
                    if (!strcmp(context,"</body>\n")){
                        fputs("\n",fpDst);
                        fputs(context,fpDst);
                        atbody=0;
                        continue;
                    }
                    continue;
                }
                fputs(context,fpDst);
            }
            rename(temp,thisfilepath);
            return;
}
void InOrder_traverse(Grammar *t)
{
    if (t) {
        InOrder_traverse(t->left);
        if (istrue) {
            printf("before replace %s\n",t->array);
            replacehtml(t->array);
        }
        printf("inorder %s\n",t->array);
        switch (t->type) {
            case 1:
                if (!strcmp(t->array, "if")) {
                    switch (operatortype) {
                        case 501:
                            if (!strcmp(eax[0], eax[1])) {
                                istrue=1;
                            }
                            break;
                    }
                }break;
            case 4:
                eax[eaxindex++] = t->array;
                break;
            case 5:
                operatoreax[operatoreaxindex] = t->array;
                if (!strcmp(operatoreax[operatoreaxindex++], "==")) {
                    operatortype = Operator_Equal;
                }
                break;
        }
        InOrder_traverse(t->right);
    }
    }

void open(char * filepath,char * uri,char * path){
    thisuri=uri;
    thisfilepath=filepath;
    thispath=path;
    FILE *fp;
    char context[101];
    if ((fp=fopen(filepath,"r"))==NULL){
        perror("file open fail");
        exit(1);
    }
    while (fgets(context,sizeof(context),fp)){
        if (!strcmp(context,"<body>\n")){
            bodydeal(fp);
            printf("body 执行完毕\n");
            break;
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (roots[i]!=NULL){
            eaxindex=0;
            InOrder_traverse(roots[i]);
        }
    }
}
void bodydeal(FILE * fp) {
    char context[101];
    char jinja[1025];
    char pln[] = "\n";
    bzero(jinja, 1025);
    while (fgets(context, sizeof(context), fp)) {
        if (!strcmp(context, "</body>\n")) break;
        strcat(jinja, context);
    }
    char *line = NULL;
    line = strtok(jinja, pln);
    char *lines[100];
    StringList *tail = headsl;
    bzero(lines, 100);
    while (line != NULL) {
        StringList *node = (StringList *) malloc(sizeof(StringList));
        tail->next = node;
        node->array = line;
        tail = node;
        List[listlen++] = node;
        line = strtok(NULL, pln);
    }
    tail = headsl->next;
    WordList * tailwd=headctl;
    char pspace[] = " ";
    char *word = NULL;
    while (tail!=NULL) {
        word = strtok(tail->array, pspace);
        while (tail != NULL && word != NULL) {
            WordList *wordnode = (WordList *) malloc(sizeof(WordList));
            tailwd->next = wordnode;
            wordnode->array = word;
            tailwd = wordnode;
            Wlist[wlistlen++] = wordnode;
            word = strtok(NULL, pspace);
        }
        tail=tail->next;
        WordList * pln=(WordList *)malloc(sizeof(WordList));
        tailwd->next=pln;
        pln->array="nextLine";
        tailwd=pln;
        Wlist[wlistlen++]=pln;
    }
    tailwd->msg="end";
    tailwd=headctl->next;
    int typeint=0;
    while (tailwd!=NULL){
        if (tailwd->msg!=NULL){
            tailwd->msg=NULL;
        }
        if (typeint){
            if (tailwd->next->next==NULL){
                tailwd->msg="part";
            } else {
                if (tailwd->next->next->msg != NULL) {
                    if (!strcmp(tailwd->next->next->msg, "end")) {
                        return;
                    }
                }
                if (!strcmp(tailwd->next->next->array, "{%")) {
                    tailwd->msg = "part";
                }
            }
        }
        if (!typeint) {
            if (!strcmp(tailwd->array, "{%")) {
                typeint = Controller;
                tailwd = tailwd->next;
                headctl=tailwd;
                continue;
            } else if (!strcmp(tailwd->array, "{{")) {
                typeint = Val;
                tailwd = tailwd->next;
                continue;
            } else if (!strcmp(tailwd->array, "{#")) {
                typeint = Define;
                tailwd = tailwd->next;
                continue;
            } else{
                typeint=Context;
                tailwd=tailwd->next;
                continue;
            }
        } else{
            if (tailwd->msg!=NULL&&!strcmp(tailwd->msg,"part")){
                tailwd->type=Fin;
                switch (typeint) {
                    case 1:docon(headctl);break;
                    case 2:break;
                    case 3:break;
                    case 4:doval(headctl);break;
                }
                typeint=0;
                tailwd=tailwd->next;
                headctl=tailwd;
                continue;
            }
            if (!strcmp(tailwd->array,"==")){
                tailwd->type=Operator;
                tailwd=tailwd->next;
                continue;
            }
        }
        tailwd=tailwd->next;
    }
}
void docon(WordList * segment){
        int isbody=0;
        char arr[101];
        int arrindex=0;
        int isbreak=0;
        Grammar * treerightchild=(Grammar *)malloc(sizeof(Grammar));
        if (!strcmp(segment->array,"if")){
                Grammar * tree=(Grammar *)malloc(sizeof(Grammar));
                tree->array=segment->array;
                tree->type=Controller;
                segment=segment->next;
                roots[trees++]=tree;
            while (1){
                    if (isbody){
                        int i = 0;
                        int len=strlen(segment->array);
                        for (;i<len;++i) {
                            arr[arrindex++]=segment->array[i];
                        }
                        arr[arrindex++]=' ';
                        segment=segment->next;
                        if (isbreak){
                            break;
                        }
                        if (segment->type==13){
                            isbreak=1;
                        }
                        continue;
                    }
                 if (segment->type==5) {
                    operatoreax[operatoreaxindex++]=segment->array;
                    segment=segment->next;
                    continue;
                }
                 if (!strcmp(segment->array,"nextLine")){
                    isbody=1;
                    segment=segment->next;
                    treerightchild->array=segment->array;
                     continue;
                 }
                eax[eaxindex++]=segment->array;
                segment=segment->next;
                if (isbreak){
                    break;
                }
                if (segment->type==13){
                    isbreak=1;
                }
            }
            treerightchild->array=arr;
            tree->right=treerightchild;
            if (!strcmp(operatoreax[0],"==")){
                if (!strcmp(eax[0],eax[1])){
                    createoperatertree(tree);
                }else {
                    return;
                }
            }
        } else if (!strcmp(segment->array,"for")){

        }
    arr[arrindex]='\0';
}
void doval(WordList * segment){
    while (segment->array==NULL)segment=segment->next;
    while (strcmp(segment->array,"nextLine")){
        if (segment->msg!=NULL&&!strcmp(segment->msg,"part"))break;
        if (segment->array[0]==':'){
            Variable * var=(Variable *) malloc(sizeof (Variable));
            var->key=segment->array;
            vareax[varindex++]=var;
        }
        segment=segment->next;
    }
    printf("vareax len %d\n",varindex);
    printf("var0 key%s\n",vareax[0]->key);
}
void createoperatertree(Grammar * tree){
    Grammar * operatornode=(Grammar *)malloc(sizeof(Grammar));
    operatornode->array=operatoreax[0];
    operatornode->type=Operator;
    tree->left=operatornode;
    Grammar * leftnode=(Grammar *)malloc(sizeof(Grammar));
    leftnode->array=eax[0];
    leftnode->type=Val;
    operatornode->left=leftnode;
    Grammar * rightnode=(Grammar *)malloc(sizeof(Grammar));
    rightnode->array=eax[1];
    rightnode->type=Val;
    operatornode->right=rightnode;
    bzero(operatoreax,10);
    bzero(eax,10);
}