#include <stdio.h>
#include <stdlib.h>

// an improvement on C's % operator - enables proper negative modulo calculation
int properMod(int a, int b) {

    if (a < 0) {
        a = a + b;
    }

    if (a < 0) {
        properMod(a, b);
    }
    else {
        return a % b;
    }
    return 0;

}

struct cipherArray {
    int length;
    int padding;
    int array[];
};

struct cipherArray *
cipherInitialize(int length, int padding){

    struct cipherArray *input;

    input = malloc(sizeof(struct cipherArray) + sizeof(int) * length);

    input->length = length;
    input->padding = padding;


}


int
main(int argc, char **argv) {

    // ensure three and only three arguments are piped in
    if (argc != 4) {
        fprintf(stderr, "Usage: ./transpose n a b\n");
        return 1;
    }

    // ensure n is at least 1
    if (argv[1] < (char *) 1) {
        fprintf(stderr, "Ensure n is at least 0\n");
    }

    int c;
    int counter = 0;

    while ((c = getchar()) != EOF) {
        counter++;
    }

    printf("%d\n", counter);

    return 0;

}