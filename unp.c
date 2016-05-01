#include "unp.h"
#include "myerror.h"

/**
 * write n bytes to file fd
 * if fail return -1, otherwise always return n
 */
int writen(int fd, char* buf, int n){
    int left = n;
    int written = 0;
    char* ptr = buf;
    while(left > 0){
        if((written = write(fd, ptr, left)) != left){
            if(written == -1 && errno != EINTR)
            {
                errMsg("writen");
                return -1;
            }
            else if(written== -1 && errno == EINTR) continue;
            else if(written >= 0){
                printf("%d written\n", written);
                left -= written;
                ptr += written;
                if(left == 0)
                    break;
            }
        }
        else
            break;
    }
    return n;
}

/**
 * read n from file fd
 * return -1 if failed
 * otherwise return number of byte read
 */
int readn(int fd, char* buf, int n){
    char* ptr = buf;
    int left = n;
    int num;
    while(left > 0){
        if((num = read(fd, buf, left)) < 0) {
            if(errno == EINTR) continue;
            else{
                errMsg("readn");
                return -1;
            }
        }
        else if(num > 0){
             ptr += num;
             left -= num;
        }
        else
            return n - left;
    }
}
