#include <stdlib.h>
#include <stdio.h>

int main(void) {
    pid_t pid = fork();
    char *arglist[] = {"/bin/ls", "-1", NULL};
    char *env[] = {NULL};

    if(pid < 0) {
        printf("Eroare: %d", (int)pid);
        return EXIT_FAILURE;
        
    }

    else {
        if(pid == 0) { // we are in child
            printf("Child process started with ID: %d\n", (int)getpid());
            execve(arglist[0], arglist, env);
        }
        else {
            printf("My PID =  %d , and child's pid is %d \n", getpid(), pid);
            wait(NULL);
            printf("Child process %d finished.\n", pid);
        }
        
    }
    
    return EXIT_SUCCESS;

}
