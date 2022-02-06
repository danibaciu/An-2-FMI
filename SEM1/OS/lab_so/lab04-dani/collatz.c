#include <stdlib.h>
#include <stdio.h>
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

int main(int argc, const char *args[]) {
    if(argc <= 1) {
        printf("Eroare: Pune si tu un numar ca si argument.\n");
        return EXIT_FAILURE;
    }
    else {
        pid_t pid = fork();
        
        if(pid < 0) {
            printf("Error: %d", (int)pid);
            return EXIT_FAILURE;
        }
        else {
            int number = atoi(args[1]);
            if(pid == 0) {
                // We are in the child processS
                printf("Child process started with ID: %d\n", getpid());
                collatzFunction(number);
            }
            else {
                // We are in the parent process;
                wait(NULL);
                printf("Done Parent %d , Child process %d finished.\n", getpid(), pid);
            }
        }
    }
    return EXIT_SUCCESS;
}
