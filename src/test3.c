#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_ALLOCS 10

int main(int argc, char* argv[]){

    char buffer[BUFSIZ];
    int  n;

    for (int i = 1; i < NUM_ALLOCS; i++){

        int *var_four = malloc(i*sizeof(int));
        n = sprintf(buffer, "var_four[%d] in Main: %p\n", i, var_four);
        write(STDOUT_FILENO, buffer, n);
        
        int *var_five = malloc(2*i*sizeof(int));
        n = sprintf(buffer, "var_five[%d] in Main: %p\n", i, var_five);
        write(STDOUT_FILENO, buffer, n);
        
        int *var_six = malloc(3*i*sizeof(int));
        n = sprintf(buffer, "var_six[%d] in Main: %p\n", i, var_six);
        write(STDOUT_FILENO, buffer, n);
        
        free(var_four);
        free(var_five);
        free(var_six);
    }

    return 0;
}

