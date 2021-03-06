#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_ALLOCS 2

int main(int argc, char* argv[]){

    char buffer[BUFSIZ];
    int  n;

    for (int i = NUM_ALLOCS; i > 0; i--){

        int *var_four = malloc(sizeof(int));
        n = sprintf(buffer, "var_four[%d] in Main: %p\n", i, var_four);
        write(STDOUT_FILENO, buffer, n);
        
        int *var_five = malloc(sizeof(int));
        n = sprintf(buffer, "var_five[%d] in Main: %p\n", i, var_five);
        write(STDOUT_FILENO, buffer, n);
        
        int *var_six = malloc(sizeof(int));
        n = sprintf(buffer, "var_six[%d] in Main: %p\n", i, var_six);
        write(STDOUT_FILENO, buffer, n);
        
        free(var_four);
        free(var_five);
        free(var_six);
    }

    return 0;
}

