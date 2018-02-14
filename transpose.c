#include <stdio.h>
#include <stdlib.h>

struct cipherArray {
    int length;
    int padding;
    char *array; // pointer to the array
};

struct cipherArray *
cipherInitialize(int length, int padding){

}


int
main(int argc, char **argv) {

    // ensure three and only three arguments are piped in
    if (argc != 4) {
        fprintf(stderr, "Usage: ./transpose n a b\n");
        return 1;
    }

    // ensure n is at least 1
    if (argv[1] > 0) {
        fprintf(stderr, "Ensure n is at least 0\n");
    }

}