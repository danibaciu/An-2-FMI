#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NTHREAD 5
#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex;

int decrease_count (int count) {
    pthread_mutex_lock(&mutex);
    //start critical section
    if ( available_resources < count ) {
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    else available_resources -= count ;
    printf("Got %d resources, %d remaining\n", count, available_resources);
    //end critical section
    pthread_mutex_unlock(&mutex);
    return 0;
}

int increase_count (int count) {
    pthread_mutex_lock(&mutex);
    //pthread_mutex_lock(&mutex_steps);
    available_resources += count;
    printf("Realised %d resources, %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mutex);
    return 0;
}

void *threadFunc(void *threadArg) {
    int nr_resurse = *(int *)threadArg;
    while (decrease_count(nr_resurse) == -1);
    //am consumat resursele alea
    increase_count(nr_resurse);
}

int main (int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t thread[NTHREAD];
    int i, arg[NTHREAD];
    pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < NTHREAD; i++){
        arg[i] = rand() % MAX_RESOURCES + 1;
        pthread_create(&thread[i], NULL, threadFunc, &arg[i]);
    }
    for(i = 0; i < NTHREAD; i++){
        pthread_join(thread[i], NULL);
    }
    printf("Nr resurse finale = %d\n", available_resources);
    return 0;
}
