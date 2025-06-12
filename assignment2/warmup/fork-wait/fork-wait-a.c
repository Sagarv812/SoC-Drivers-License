#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Calling fork() N times gives 2^N total processes and 2^N - 1 child processes

int main(int argc, char *argv[])
{
    printf("God Parent: %d\n\n", (int)getpid());

    int n = atoi(argv[1]);

    pid_t pid;

    for (int i = 0; i < n; i++)
    {
        if ((pid = fork()) == 0)
        {
            printf("Child %d with Parent %d\n", (int)getpid(), (int)getppid());
        }
        else if (pid > 0)
        {
            int pid_wait = wait(NULL);
            printf("Child %d died noooooo :( Parent %d carries on\n", pid_wait, (int)getpid());
        }
    }
}