#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// an improvement on C's % operator - enables proper negative modulo calculation
int properMod(int a, int b) {

    // adds the b value to a
    if (a < 0) {
        a = a + b;
    }

    // if a is still negative, call the function again
    if (a < 0) {
        properMod(a, b);
    }

    // else, we can return the modulo call
    else {
        return a % b;
    }

    return 0;
}

// returns the proper size of the intended array based upon text length and block size
int arraySize(int textLength, int blockSize){

    int size;

    // if the blocksize is larger than the length, add the extra spaces to the size
    if (textLength - blockSize < 0) {
        size = blockSize;
        return size;
    }
    /* else, see if textLength is a multiple of blockSize
     * if it is, return textLength as the proper size
     * if it isn't, determine the next nearest multiple of block size that will cover the text */
    else {
        switch(properMod(textLength, blockSize)){
            case 0 :
                size = textLength;
                break;
            default :
                size = ((textLength / blockSize) + 1) * blockSize;
        }
        return size;
    }
}

// a struct for a cipher array
struct cipherArray {
    int length;
    int blockSize;
    int array[];
};

/* sets the element of the array to the given value; bounds checking is implemented
 * based upon vector set from lecture */
void
cipherSet(struct cipherArray *array, int index, int value) {

    assert(index >= 0 && index < array->length );

    array->array[index] = value;
}

// utilized from packageVector.c
void
printArray(int length, const int *a) {
    for (int i = 0; i < length; i++) {
        printf("%c ", a[i]);
    }
}

// utilized from packageVector.c
void
cipherPrint(const struct cipherArray *c)
{
    printArray(c->length, c->array);
}

void
freeCipher(struct cipherArray *array){
    free(array);
}

/* given a pointer to a cipherArray struct, initialize it with the proper amount of space
 * and the buffered \0 characters */
struct cipherArray *
cipherInitialize(int length, int textLength, int blockSize){

    struct cipherArray *input;

    input = malloc(sizeof(struct cipherArray) + sizeof(int) * length);

    input->length = length;
    input->blockSize = blockSize;

    // if necessary, pad the remaining blocks with \0
    for (int i = textLength; i < length; i++ ){
        cipherSet(input, i, '\0');
    }

    printf("%d\n", length);
    return input;
}


int
main(int argc, char **argv) {

    //freopen("example.txt", "r", stdin);

    // convert pointers to strings into ints
    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);

    // ensure three and only three arguments are piped in
    if (argc != 4) {
        fprintf(stderr, "Usage: ./transpose n a b\n");
        return 1;
    }

    // ensure n is at least 1
    if (n < 1) {
        fprintf(stderr, "Ensure n is at least 0\n");
    }

    // get the length of the input so we can create a proper array
    int c;
    int length;


    char user_input[10000];
    fgets(user_input, 10000, stdin);

    length = (int) strlen(user_input);

    printf("%d\n", length);

    // create cipherArray struct and initialize it.
    struct cipherArray *inputArray;
    inputArray = cipherInitialize(arraySize(length, n), length, n);

    // create an output array for our transposed message
    struct cipherArray *outputArray;
    outputArray = cipherInitialize(arraySize(length, n), length, n);

    // place stdin into inputArray
    for (int x = 0; x < length; x++) {
        cipherSet(inputArray, x, user_input[x]);
    }

    int numOfBlocks = inputArray->length/n;
    printf("%d / % d = %d\n", inputArray->length, n, numOfBlocks);

    for (int x = 0; x < numOfBlocks; x++) {

        int multiplier =  x*n;

        for (int y = 0; y < n; y++){

            int originalIndex = multiplier + y;
            int transposedIndex = multiplier + properMod((a*y + b), n);

            cipherSet(outputArray, originalIndex, inputArray->array[transposedIndex]);
        }


    }

    cipherPrint(outputArray);

    // free up memory
    freeCipher(inputArray);
    freeCipher(outputArray);

    return 0;

}