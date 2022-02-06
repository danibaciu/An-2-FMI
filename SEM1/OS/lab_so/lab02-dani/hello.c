#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(void) {

    write(1, "Hello test", sizeof("Hello test") - 1);

    return EXIT_SUCCESS;
}
