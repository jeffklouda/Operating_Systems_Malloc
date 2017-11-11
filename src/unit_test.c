#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
   

    int* one = malloc(10*sizeof(int));    
    int* two = malloc(50*sizeof(int));
    
    if (one)
        write(STDOUT_FILENO, "[X] Struct Block Test[1] Success\n", 33);
    else
        write(STDOUT_FILENO, "[ ] Struct Block Test[2] Failure\n", 33);
    
    if (two)
        write(STDOUT_FILENO, "[X] Struct Block Test[2] Success\n", 33);
    else
        write(STDOUT_FILENO, "[ ] Struct Block Test[2] Failure\n", 33);
    

    free(one);  
    free(two);

    return 0;
}

