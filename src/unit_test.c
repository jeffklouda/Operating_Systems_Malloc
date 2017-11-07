#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
   
    
    struct block test_block;
    struct block* block_ptr = NULL;
    block_ptr = &test_block;
    if (block_ptr)
        write(STDOUT_FILENO, "[X] Struct Block Test Success\n", 30);
    else
        write(STDOUT_FILENO, "[ ] Struct Block Test Failure\n", 30);
        
    struct block* last = test_block;
    struct block* test_ptr = grow_heap(&test_block, 12);
    

    return 0;
}
