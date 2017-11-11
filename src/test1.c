#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_ALLOCS 10

int main(int argc, char* argv[]){

    char buffer[BUFSIZ];
    int  n;

    for (int i = NUM_ALLOCS; i > 0; i--){
        int *var_four = malloc(1*sizeof(int));
        n = sprintf(buffer, "Pointer[%d] in Main: %p\n", i, var_four);
        write(STDOUT_FILENO, buffer, n);
        free(var_four);
    }

    return 0;
}

