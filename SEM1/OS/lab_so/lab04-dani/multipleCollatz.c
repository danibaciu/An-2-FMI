#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


void collatzFunction(int n) {
printf("%d : ", n);
    while(n != 1) {
        printf("%d ", n);
        if(n % 2 == 0) {
            n = n / 2;
        }
        else {
            n = 3 * n + 1;
        }
    }
    
}



int main(int argc, const char *args[])
{
    if(argc <= 1) {
        printf("Pune si tu mai multe argumente.\n");
        return EXIT_FAILURE;
    }
    else {
        
        char *env[] = {NULL};
        printf("Starting parent process with the PID= %d\n", getpid());
        for(int i = 1; i < argc; i++) {
            pid_t pid = fork();
            
            if(pid < 0) {
                printf("Eroare %d:\n", (int)pid);
                return EXIT_FAILURE;
            }
            else if(pid == 0) {
                int x = atoi(args[i]);
		collatzFunction(x);
		printf("Parent %d : Child %d finished \n",getppid(), getpid());
		exit(1);
            }
            
        }
        for(int i = 1; i <argc; i++) {
            wait(NULL);
        }
    }
    return EXIT_SUCCESS;
}
