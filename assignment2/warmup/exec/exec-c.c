#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//The print statement after execvp prints when execvp fails and returns -1

int main(int argc, char *argv[]){
        pid_t pid;
        if ((pid=fork())==0){
                char *myargs[2];
                myargs[0] = strdup("womp");
                myargs[1] = strdup("womp");
                myargs[2] = NULL;
                printf("Yayy before exec hahaha\n");
                execvp(myargs[0], myargs);
                printf("Uhh after exec helpp\n");
        }else if(pid>0){
                int pid_wait = waitpid(pid,NULL,0);
        }
}