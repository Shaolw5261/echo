#include "unp.h"
#include "myerror.h"

int writen(int sockefd, char* buf, int n){
    int left = n;
    int written = 0;
    char* ptr = buf;
    while((written = write(sockefd, ptr, left)) > 0){
        ptr = buf + written;
        left = n - written;
        if(left == 0)
            break;
    }
    if(written == -1){
        errMsg("writen");
        return -1;
    }
    return 0;
}
