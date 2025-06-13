#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
        pid_t pid;
        if ((pid=fork())==0){
                char *myargs[2];
                myargs[0] = strdup("ls");
                myargs[1] = strdup("-l");
                myargs[2] = NULL;
                execvp(myargs[0], myargs);
        }else if(pid>0){
                int pid_wait = waitpid(pid,NULL,0);
        }
}