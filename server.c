#include "unp.h"
#include <stdio.h>
#include <stdlib.h>
#include "myerror.h"
#include <signal.h>

#define PORT 8687
#define BUFSIZE 1000

void str_echo(int);
void sig_child(int sig);

int main(int argc, char* argv[]){
    int listenfd; //server socket file descriptor
    int connfd;

    signal(SIGCHLD,sig_child);
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
         printf("connect from %s:%d\n", inet_ntoa(connaddr.sin_addr),htons(connaddr.sin_port));
         if(connfd == -1){
              errMsg("connect");
              exit(-1);
         }
         if(fork() == 0){
             close(listenfd);
             //echo str
             str_echo(connfd);
             close(connfd);
             printf("connection closed!\n");
             exit(0);
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
       //printf("read %d bytes from peer\n", n);
       int ret =  writen(connfd,buf,n);
       if(ret == -1){
           break;
       }
       //printf("write %d bytes to peer\n", ret);
    }
    if(n < 0 && errno == EINTR){//read was interrupted
        goto again;
    }
    else if(n < 0){
        errMsg("read");
    }
}

void sig_child(int sig){
     pid_t pid;
     int stat;
     //pid = wait(&stat);
     while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
         printf("child %d terminated\n", pid);
     return;
}
