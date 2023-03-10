/* Code to test buffering input/output data */

/*
With this design, the only thing that would need to change is the levels
of the multi level stack to hold buffers, the macros to detrmine the size of number of buffers,
at each specified level, and using that to change initializeBuffers(). As a result, the only
substantial changes needed are for initializing the buffers depending on use case.
The remove, insert, and structs will stay the same from mission to mission.
*/



#include "../include/PSP.h"


/* Initialize buffers, both big and small */
int initializeBuffers() {
    struct buffer *new;
    struct buffer *old;

    /* Allocate big sized buffers */
    for (int i = 0; i < BIGNUMBUFFERS; i++) {
        new = (struct buffer *)malloc(STRUCTBUFFERSIZE + BIGMAXSIZEBUFFER);
        new->size = BIGMAXSIZEBUFFER;
        if (i == 0) {
            multiLevelStack[2].next = new;
            multiLevelStack[2].size = BIGMAXSIZEBUFFER;
        } else {
            old->next = new;
        }
        old = new;
    }
    /* Allocate medium sized buffers */
    for (int i = 0; i < MEDNUMBUFFERS; i++) {
        new = (struct buffer *)malloc(STRUCTBUFFERSIZE + MEDMAXSIZEBUFFER);
        new->size = MEDMAXSIZEBUFFER;
        if (i == 0) {
            multiLevelStack[1].next = new; //Changed per for loop
            multiLevelStack[1].size = MEDMAXSIZEBUFFER;
        } else {
            old->next = new;
        }
        old = new;
    }
    /* Allocate small sized buffers */
    for (int i = 0; i < SMALLNUMBUFFERS; i++) {
        new = (struct buffer *)malloc(STRUCTBUFFERSIZE + SMALLMAXSIZEBUFFER);
        new->size = SMALLMAXSIZEBUFFER;
        if (i == 0) {
            multiLevelStack[0].next = new; //Changed per for loop
            multiLevelStack[0].size = SMALLMAXSIZEBUFFER;
        } else {
            old->next = new;
        }
        old = new;
    }

    return 1;
}

/* Remove and return buffer based on size */
struct buffer * requestBuffer(int inputSize) {
    struct buffer * output;
    //Find correct level that fits size
    for (int i = 0; i < LEVELS; i++) {
        if (multiLevelStack[i].size >= inputSize) {
            output = multiLevelStack[i].next;
            multiLevelStack[i].next = output->next;
            output->next = NULL;
            return output;
        }
    }
    return NULL;
}

/* Insert buffer based on size field */
int inputBuffer(struct buffer *input) {
     //Find correct level that fits size
    for (int i = 0; i < LEVELS; i++) {
        if (multiLevelStack[i].size >= input->size) {
            input->next = multiLevelStack[i].next;
            multiLevelStack[i].next = input;
            return 1;
        }
    }
    return -1;
    
}

/* Debugging function to print multiLevelStack */
void printMultiLevelStack() {
    for (int i = 0; i < LEVELS; i++) {
        struct buffer * head = multiLevelStack[i].next;
        int c = 0;
        while (head != NULL) {
            c++;
            head = head->next;
        }
        fprintf(stderr, "Number of buffers at %d is: %d\n", i, c);
    }

}
