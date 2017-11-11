/* malloc.c: simple memory allocator -----------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

/* Macros --------------------------------------------------------------------*/

#define ALIGN4(s)           (((((s) - 1) >> 2) << 2) + 4)
#define BLOCK_DATA(b)       ((b) + 1)
#define BLOCK_HEADER(ptr)   ((struct block *)(ptr) - 1)

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define COUNTER_WRITE(str, num) str STR(num) "\n"

#define WRITER(buf, str, integer) sprintf(buf, str, integer)

/* Block structure -----------------------------------------------------------*/

struct block {
    size_t        size;
    struct block *next;
    bool          free;
};

/* Global variables ----------------------------------------------------------*/

struct block *FreeList     = NULL;
struct block *last_checked = NULL;

/* TODO: Add counters for mallocs, frees, reuses, grows */
size_t num_mallocs   = 0;
size_t num_frees     = 0;
size_t num_reuses    = 0;
size_t num_requests  = 0;
size_t num_splits    = 0;
size_t num_coalesces = 0;
size_t num_blocks    = 0;
size_t mem_requested = 0;
size_t max_heap_size = 0;

bool atexit_check = true;

int new_stdout;

void print_counters(void){
    
    char buffer[BUFSIZ];
    int n;
    
    n = sprintf(buffer, "mallocs:   %zu\n", num_mallocs);
    write(new_stdout, buffer, n);  
    n = sprintf(buffer, "frees:     %zu\n", num_frees);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "reuses:    %zu\n", num_reuses);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "grows:     %zu\n", num_requests);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "splits:    %zu\n", num_splits);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "coalesces: %zu\n", num_coalesces);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "blocks:    %zu\n", num_blocks);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "requested: %zu\n", mem_requested);
    write(new_stdout, buffer, n);
    n = sprintf(buffer, "max heap:  %zu\n", max_heap_size);
    write(new_stdout, buffer, n);
    
}

/* Find free block -----------------------------------------------------------*/


struct block *find_free(struct block **last, size_t size) {
    struct block *curr = FreeList;

#if defined FIT && FIT == 0
    /* First fit */
    while (curr && !(curr->free && curr->size >= size)) {
        *last = curr;
        curr  = curr->next;
    }
#endif
    /* TODO: Support other policies */

#if defined FIT && FIT == 1
    /* Next fit */
    if (last_checked){
        curr = last_checked;
    }
    while (curr && !(curr->free && curr->size >= size)) {
        *last = curr;
        curr = curr->next;
    }
    if (!curr && FreeList){
        curr = FreeList;
        while (curr && !(curr->free && curr->size >= size)){
            *last = curr;
            curr = curr->next;
        }
   }
   if (curr){
        last_checked = curr;   
   }
#endif

#if defined FIT && FIT == 2
    /* Best fit */
    struct block *best_block = NULL;
    while (curr) {
        if (curr->free && curr->size >= size && (!best_block || curr->size < best_block->size)) {
            best_block = curr;
        }
        *last = curr;
        curr = curr->next;
    }
    curr = best_block;
#endif

#if defined FIT && FIT == 3
    /* Worst fit */
    struct block *worst_block = NULL;
    while (curr) {
        if (curr->free && curr->size >= size && (!worst_block || curr->size > worst_block->size)) {
            worst_block = curr;
        }
        *last = curr;
        curr = curr->next;
    }
    curr = worst_block;
#endif

    return curr;
}

/* Grow heap -----------------------------------------------------------------*/

struct block *grow_heap(struct block *last, size_t size) {
    /* Request more space from OS */
    struct block *curr = (struct block *)sbrk(0);
    struct block *prev = (struct block *)sbrk(sizeof(struct block) + size);

    assert(curr == prev);

    /* OS allocation failed */
    if (curr == (struct block *)-1) {
        return NULL;
    }

    /* Update FreeList if not set */
    if (FreeList == NULL) {
        FreeList = curr;
        last_checked = FreeList;   
    }

    /* Attach new block to prev block */
    if (last) {
        last->next = curr;
    }

    /* Update block metadata */
    curr->size = size;
    curr->next = NULL;
    curr->free = false;
    return curr;
}

/* Allocate space ------------------------------------------------------------*/

void *malloc(size_t size) {

    if (atexit_check) {
        dup2(STDOUT_FILENO, new_stdout);       
        int i = atexit(print_counters);
        if (i != 0){
            exit(EXIT_FAILURE);
        }
        atexit_check = false;
    }


    /* Align to multiple of 4 */
    size = ALIGN4(size);

    /* Handle 0 size */
    if (size == 0) {
        return NULL;
    }

    /* Look for free block */
    struct block *last = FreeList;
    struct block *next = find_free(&last, size);

    /* Increment num_reuses if a block is reused */
    if (next){
        num_reuses++;
    }

    /* Split free block? */
    if ( next && (next->size > (size + sizeof(struct block))) ) {
    

        struct block *new_block = next;

        char *block_char = (char*)new_block + sizeof(struct block) + size;

        new_block = (struct block*)block_char; 
        
        new_block->next = next->next;
        new_block->free = true;
        new_block->size = next->size - sizeof(struct block) - size;
        
        next->next  = new_block; 
        next->free  = false;
        next->size  = size;
        
        num_splits++;    
        num_blocks++;
        
        
    }   
    

    /* Could not find free block, so grow heap */
    if (next == NULL) {
        num_requests++;

        next = grow_heap(last, size);
        if (next){
            num_blocks++;
            max_heap_size += size;
        }
    }

    /* Could not find free block or grow heap, so just return NULL */
    if (next == NULL) {
        return NULL;
    }
    
    /* Mark block as in use */
    next->free = false;

    /* Increment num_mallocs */
    num_mallocs++;
    mem_requested += size;

    /* Return data address associated with block */
    return BLOCK_DATA(next);
}


/* Reclaim space -------------------------------------------------------------*/
bool coalesce_check(struct block *free_pointer){
    char * free_ptr_char = (char*)free_pointer;
    free_ptr_char = free_ptr_char + sizeof(struct block) + free_pointer->size;
    return (free_pointer->next && free_pointer->free && free_pointer->next->free && (free_pointer->next == (struct block*)(free_ptr_char)));
}

void free(void *ptr) {
    
    if (ptr == NULL) {
        return;
    }
    

    /* Make block as free */
    struct block *curr = BLOCK_HEADER(ptr); 
   
    assert(curr->free == 0);
    curr->free = true;

    /* Coalesce free blocks? */

    if (coalesce_check(curr)) {
   
        num_coalesces++;
        num_blocks--;
       
        curr->size = curr->size + curr->next->size + sizeof(struct block);
        curr->next = curr->next->next;
    }

    /* Increment num_frees */
    num_frees++;
 
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=cpp: --------------------------------*/
