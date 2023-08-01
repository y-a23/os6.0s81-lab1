#include "kernel/types.h"
#include "user/user.h"
void function(int pipe_out)
{
    int p[2];
    pipe(p);
    int cur;
    int num;
    if(read(pipe_out,&cur,4)!=4)//读出旧pipe输出端口的第一个数然后打印
    {
        exit(1);
    }
    printf("prime %d\n",cur);
    int ret=read(pipe_out,&num,4);
    if(ret==0)exit(0);//如果旧pipe只有一个数，不用fork直接退出（递归结束条件）
    else 
    {
        while(ret)
        {
            if(num%cur!=0)
            {
                write(p[1],&num,4);//创建一个新pipe，然后将drop筛除之后的数写入
            }
            ret=read(pipe_out,&num,4);
        }
    }
    close(pipe_out);
    close(p[1]);
    if(fork()==0)
    {
        function(p[0]);//子进程递归
    }
    else
    {
        wait(0);
    }
    exit(0);
}

int main(int argc,char* argv[])
{
    int p[2];
    pipe(p);
    for(int i=2;i<36;i++)
    {
        write(p[1],&i,sizeof(int));//写入到管道输入端
    }
    close(p[1]);//写完关闭
    function(p[0]);
    exit(0);
}