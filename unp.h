#ifndef UNP_H
#define UNP_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define LISTENQ 200
int writen(int socketfd, char* buf, int n);


#endif

