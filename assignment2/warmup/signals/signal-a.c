#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    if ((pid = fork()) == 0)
    {
        while (1)
            sleep(1);
    }
    else if (pid > 0)
    {
        sleep(2);
        kill(pid, 9);
        int pid_wait = waitpid(pid, NULL, 0);
        printf("Child is finally dead hahaha\n");
    }
    return 0;
}