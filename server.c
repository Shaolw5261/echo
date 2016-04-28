#include "unp.h"
#include "stdio.h"
#include "stdlib.h"
#include "myerror.h"

#define PORT 8687
#define BUFSIZE 1000

void str_echo(int);

int main(int argc, char* argv[]){
    int listenfd; //server socket file descriptor
    int connfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in connaddr;
    socklen_t connaddr_len;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    //create a listen socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        errMsg("socket");
        exit(-1);
    }

    //bind
    int ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret == -1){
        errMsg("bind");
        exit(-1);
    }

    //listen
    listen(listenfd, LISTENQ);

    for(;;){
         connfd = accept(listenfd,(struct sockaddr*)&connaddr,&connaddr_len);
         if(connfd == -1){
              errMsg("connect");
              exit(-1);
         }
         if(fork() == 0){
             close(listenfd);
             //echo str
             str_echo(connfd);
             close(connfd);
         }
         close(connfd);
    }
}

/**
 * echo string to client
 */
void str_echo(int connfd){
     //read line from client
    char buf[BUFSIZE];
    int n;
again:
    while((n = read(connfd,buf,BUFSIZE)) > 0){
       int ret =  writen(connfd,buf,n);
       if(ret == -1){
           break;
       }
    }
    if(n < 0 && errno == EINTR){//read was interrupted
        goto again;
    }
    else if(n < 0){
        errMsg("read");
    }
}
