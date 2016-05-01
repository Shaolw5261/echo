#include "unp.h"
#include "myerror.h"
#include <stdio.h>
#include <string.h>

#define PORT 8687
#define BUFSIZE 1000
int main(int argc, char* argv[]){
    int sockfd;
    struct sockaddr_in addr;
    char buf[BUFSIZE];

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port =  htons(PORT);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(sockfd,(struct sockaddr*)&addr, sizeof(addr)) == -1){
        errMsg("connect");
        exit(-1);
    }

    printf(">>");
    while(fgets(buf, BUFSIZE, stdin)){
        //printf("read from stdin:%s\n", buf);
        int len = strlen(buf) + 1;
        //write to server
        if(writen(sockfd, buf,len) == -1){
             break;
        }

        //printf("write to server\n");
        //read from server
        int n;
        char* ptr = buf;
again:
        while((n = read(sockfd,ptr,len) )> 0){
            //write to stdout
            //printf("read %d bytes from server\n", n);
            ptr += n;
            len -= n;
        }
        if(n < 0 && errno == EINTR) goto again;
        else if(n < 0){
             errMsg("read");
        }
        printf("%s", buf);
        printf(">>");
    }
}
