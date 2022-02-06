#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

struct threadArg {
    int i, j, p;
};

typedef struct threadArg threadArg;

int a[100][100], b[100][100], c[100][100];

void * threadFunc (void* arg) {
    threadArg* passedArg = (threadArg*) arg;
    int * returnVal = malloc(sizeof(int));
    (*returnVal) = 0;
    for(int i = 0; i < passedArg -> p; i++){
        (*returnVal) += a[passedArg -> i][i] * b[i][passedArg -> j];
    }
    return returnVal;
}

int main (int argc, char* argv[]) {
    int m, p, n;
    printf("Introduceri dimensiunile celor 2 matrice: n,p,m :\n");
    scanf("%d%d%d",&n,&p,&m);
    printf("Introduceti cele 2 matrice\n");
    printf("Prima matrice :\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < p; j++){
            scanf("%d", &a[i][j]);
        }
    }
    printf("A doua matrice :\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < m; j++){
            scanf("%d", &b[i][j]);
        }
    }
    pthread_t thr[n][m];
    void* thrRetVal[n][m];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            threadArg* passedArg = malloc(sizeof(threadArg));
            passedArg->i = i;
            passedArg->j = j;
            passedArg->p = p;
            if (pthread_create(&thr[i][j], NULL, threadFunc, passedArg)) {
                perror("Nu se poate crea un thread nou ...");
                return errno;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (pthread_join(thr[i][j], &thrRetVal[i][j])){
                perror("Nu se poate join ...");
                return errno;
            }
            c[i][j] = (*(int*)thrRetVal[i][j]);
        }
    }
    printf("Matricea produs: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
