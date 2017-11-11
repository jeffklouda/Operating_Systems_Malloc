#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_ALLOCS 100000

int main(int argc, char* argv[]){


    for (int i = NUM_ALLOCS; i > 0; i--){
        int *var_four = malloc(1*sizeof(int));
        free(var_four);
    }

    return 0;
}

