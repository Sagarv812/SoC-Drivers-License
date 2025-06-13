#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void new_signal(int sig)
{
    printf("I will run forever\n");
}

int main(int argc, char *argv[])
{

    (void)signal(SIGINT, new_signal);
    while (1)
        sleep(1);
    return 0;
}