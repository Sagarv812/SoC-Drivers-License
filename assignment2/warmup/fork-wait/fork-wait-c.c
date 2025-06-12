#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    pid_t pid;

    if((pid=fork())==0){
        printf("Child PID: %d\n", (int)getpid());
    }else if(pid>0){
        int pid_wait = waitpid(pid, NULL, 0);
        printf("My child %d is dead :(\n", pid);
    }
}