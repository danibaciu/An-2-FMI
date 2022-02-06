#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv) {

    int fileDescriptor = open(argv[1], O_RDWR|O_APPEND, S_IRUSR | S_IWUSR);
    int fileDescriptorDest = open(argv[2], O_CREAT|O_RDWR|O_APPEND, S_IRUSR | S_IWUSR);

    if(fileDescriptor < 0) {
        printf("Error: could not open the first file");
        exit(errno);
    }

    if(fileDescriptorDest < 0){
        printf("Error: could not open the second file\n");
        exit(errno);
    }
    int readFromFile1;
    char buff[4096];

    while((readFromFile1 = read(fileDescriptor, buff, 4096)) > 0) {
        write(fileDescriptorDest, buff, readFromFile1);
    }

    close(fileDescriptor);
    close(fileDescriptorDest);
    return EXIT_SUCCESS;
}
