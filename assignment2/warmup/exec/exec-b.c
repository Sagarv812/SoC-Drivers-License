#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        pid_t pid; 
        if ((pid = fork()) == 0)
        {
            char *myargs[3];
            myargs[0] = argv[1];
            myargs[1] = argv[2];
            myargs[2] = NULL;
            execvp(myargs[0], myargs);

            exit(1);
        }
        else if (pid > 0)
        {

            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                printf("Command successfully completed.\n");
            }
            else
            {
                printf("Child not terminated normally.\n");
            }
        }
    }
    else
    {
        printf("Incorrect number of arguments\n");
    }
}