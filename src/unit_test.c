#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   

    int* one = malloc(10*sizeof(int));    

    /*
    if (block_ptr)
        write(STDOUT_FILENO, "[X] Struct Block Test Success\n", 30);
    else
        write(STDOUT_FILENO, "[ ] Struct Block Test Failure\n", 30);
    */

    free(one);  

    return 0;
}

