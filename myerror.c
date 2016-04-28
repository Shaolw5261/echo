#include "myerror.h"
#include <stdio.h>
#include <string.h>

void outputError(char* formate, va_list vp, int errorNum){
    #define BUFSIZE 500
    char buf[BUFSIZE];
    char userMsg[BUFSIZE];
    char errorText[BUFSIZE];
    vsnprintf(userMsg, BUFSIZE, formate, vp);//生成用户消息字符串
    snprintf(errorText, BUFSIZE,"%s", strerror(errorNum));
    snprintf(buf,BUFSIZE, "ERROR %s: %s\n", errorText, userMsg);
    printf("%s",buf);
}

void errMsg(char* formate, ...){
    va_list argList;
    va_start(argList, formate);//获取可变参数的起始地址
    int errorNum = errno;
    outputError(formate, argList, errorNum);
    va_end(argList);
}
