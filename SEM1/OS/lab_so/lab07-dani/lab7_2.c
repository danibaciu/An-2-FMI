#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int N;

int threads_at_barrier;
pthread_mutex_t mutex;
sem_t semaphore;

void barrier_point() {
    pthread_mutex_lock(&mutex);
    threads_at_barrier++;
    if (threads_at_barrier == N) {
        //dam drumu tuturor firelor de executie
        for (int i = 1; i <= N; i++) {
            sem_post(&semaphore);
        }
        threads_at_barrier = 0
    }
    pthread_mutex_unlock(&mutex);
    sem_wait(&semaphore);
}

void *tfun(void *v)
{
    int *tid = (int *) v ;
    printf ("%d reached the barrier\n", *tid );
    barrier_point();
    printf ("%d passed the barrier\n" , *tid );
    free(tid);
    return NULL ;
}

int main () {
    printf("N = ");
    scanf("%d", &N);

    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0, 0);

    pthread_t thread[N];
    int i, *arg[N];

    for(i = 0; i < N; i++){
        arg[i] = (int*) malloc(sizeof(int));
        *arg[i] = i;
        pthread_create(&thread[i], NULL, tfun, arg[i]);
    }
    for(i = 0; i < N; i++){
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);
    return 0;
}
