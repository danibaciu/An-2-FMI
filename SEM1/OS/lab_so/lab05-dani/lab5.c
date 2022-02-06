#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

    char shm_name[] = "collatz_dani";

    int page_size = getpagesize(), n = argc - 1, shm_size = n * page_size, shm_fd = shm_open(shm_name, O_CREAT | O_RDWR , 0666);

    if ( ftruncate ( shm_fd , shm_size ) == -1) {
        perror ( NULL );
        shm_unlink ( shm_name );
        return errno ;
    }

    char *shm_ptr = mmap( NULL, shm_size , PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("Start parinte %d\n", getpid());
    pid_t pid;

    for (int i = 0; i < n; i++) {
        pid = fork();
        if (pid == 0) {
            int current = atoi(argv[i+1]), offset = i * page_size;
            while (current != 1) {
                int written = sprintf(shm_ptr+offset,"%d ",current);

                offset = offset + written;
                current = (current % 2 == 0) ? current / 2 : 3 * current + 1;
            }
            printf("Stop Parinte %d Copil %d .\n" , getppid(), getpid());
            munmap(shm_ptr, shm_size);
            exit(1);
        }
    }
    //afisarea
    if (pid > 0) {
        while (wait(NULL) > 0 );

        for(int i = 0; i < n; i++) {
            //afisare nr de start
            printf("%s: ",argv[i+1]);
            int offset = i * page_size;
            //afisare numere din ipoteza collatz
            printf("%s 1 \n",shm_ptr + i * page_size);
        }
        printf("Stop Parinte %d Copil %d .\n" , getppid(), getpid());
        munmap(shm_ptr, shm_size);
        shm_unlink(shm_name);
    }
}
