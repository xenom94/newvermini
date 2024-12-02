#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>


int main()
{
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();

    if(pid == 0)
    {
        close(fd[1]);
        char buf[1024];
        read(fd[0],buf , sizeof(buf));
        printf("Child received: %s\n", buf);
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        write(fd[1], "Hello, World!", 13);
        close(fd[1]);
        wait(NULL);
    }

}