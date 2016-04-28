#ifndef MYERROE_H
#define MYERROR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h> //用于可变参数的头文件
#include <errno.h>

void outputError(char* formate, va_list vp, int errorNum);

void errMsg(char* formate, ...);

#endif
