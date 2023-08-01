#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char*argv[])
{
    char buffer[]={'a'};
    int fd1[2],fd2[2];
    pipe(fd1);
    pipe(fd2);
    if(fork()==0){
        close(fd1[1]);
        close(fd2[0]);
        if(read(fd1[0],buffer,1)!=1){
            exit(1);
        }
        printf("%d: received ping\n", getpid());

        
        if(write(fd2[1],buffer,1)!=1){
            exit(1);
        }
        exit(0);
    }
    else{
        close(fd1[0]);
        close(fd2[1]);
        if(write(fd1[1],buffer,1)!=1){
            exit(1);
        }
        if(read(fd2[0],buffer,1)!=1){
            exit(1);
        }
        printf("%d: received pong\n",getpid());
        exit(0);
    }

}