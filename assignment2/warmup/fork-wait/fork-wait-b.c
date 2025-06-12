#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Forking without wait() prints the statements in a random order
//To ensure that parent's statements are always printed after child, we use wait() statement in parent.

int main(int argc, char *argv[]){
    pid_t pid;

    if((pid=fork())==0){
        printf("I am child\n");
    }else if(pid>0){
        int pid_wait = wait(NULL);
        printf("I am parent\n");
        printf("My child %d is dead nooooo :(\n", pid);
    }
}