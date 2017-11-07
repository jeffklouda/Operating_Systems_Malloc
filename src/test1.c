#include <stdlib.h>


int main(int argc, char* argv[]){

    int *var_one = malloc(1000*sizeof(int));
    int *var_two = malloc(2*sizeof(int));
    int *var_three = malloc(4*sizeof(int));

    free(var_one); 
    free(var_two);
    free(var_three);

    
    for (int i = 29; i > 0; i--){
        int *var_four = malloc(i*sizeof(int));
        free(var_four);
    }

    return 0;
}

