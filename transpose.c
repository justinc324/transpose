#include <stdio.h>

int main(int argc, char **argv) {

    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }
}