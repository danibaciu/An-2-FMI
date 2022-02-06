#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

struct threadArg {
    char* c;
};

typedef struct threadArg threadArg;

void* threadFunc (void* arg) {
    threadArg* a = (threadArg*) arg;
    int length = strlen (a -> c);
    char* returnVal = malloc (length * (sizeof (char)));
    for(int i = 0; i < length; i++){
        returnVal[i] = a -> c[length - i - 1];
    }
    return returnVal;
}

int main (int argc, char* argv[]) {
    pthread_t thr;
    void * thrRetVal;
    threadArg a;
    if(!argv[1]) {
        printf("Introdu un string ...");
        return -1;
    }
    a.c = argv[1];
    if ( pthread_create(&thr, NULL, threadFunc, &a)) {
        perror("Nu s-o putut ...");
        return errno;
    }
    if ( pthread_join(thr, &thrRetVal)) {
        perror("Nu se poate join");
        return errno;
    }
    printf("You pass the test and your answer is : %s", (char*)thrRetVal);
    return 0;
}
