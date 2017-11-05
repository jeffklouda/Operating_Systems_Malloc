CSE.30341.FA17: Project 04
==========================

This is the documentation for [Project 04] of [CSE.30341.FA17].

Members
-------

1. Jeff Klouda (jklouda1@nd.edu)
2. Matthew D'Alonzo (mdalonz1@nd.edu)

Design
------

> 1. You will need to implement splitting of free blocks:
>
>   - When should you split a block?
>
>   You should split a block whenever you want to use a block and that block is larger than the space you need.
>
>   - How should you split a block?
>
>   When you want to split a block, you allocate a block struct after the amount of bytes you want to leave for what you want to allocate, you point the next pointer of `struct block *next` to the newly allocated block struct, and then you point the next pointer of the new block struct to `struct block *next`'s original next pointer.  
>
Response.

> 2. You will need to implement coalescing of free blocks:
>
>   - When should you coalescing block?
>
>   You should coalesce a block when you have multiple free blocks that are contiguous in the FreeList and in memory.
>
>   - How should you coalesce a block?
>
>   When you want to coalesce, you add the sizes of the two contiguous blocks (sizeof(data1)+sizeof(struct block)+sizeof(data2)), and then you point the next pointer of the newly coalesced block to the next pointer of the next pointer.   
>
Response.

> 3. You will need to implement Next Fit.
>
>   - What information do you need to perform a Next Fit?
>
>   You need to know the place of the last block you allocated, and the size of the allocation. 
>
>   - How would you implement Next Fit?
>
>   You start where you last allocated and you iterate from there until you find a place you can allocate.
>

Response.

> 4. You will need to implement Best Fit.
>
>   - What information do you need to perform a Best Fit?
>
>   The head of the free list, and the size that you need to allocate.
>
>   - How would you implement Best Fit?
>
>   You increment through the list, and when you find a smaller free block that can fit your allocation, you mark that one as the right one. When you finish iterating, you choose that one.
>

Response.

> 5. You will need to implement Worst Fit.
>
>   - What information do you need to perform a Worst Fit?
>
>   The head of the free list, and the size that you need to allocate.
>
>   - How would you implement Worst Fit?
>
>   You iterate through the list, and when you find a bigger block to use, you choose that one.
>

Response.

> 6. You will need to implement tracking of different information.
>
>   - What information will you want to track?
>
>   # of mallocs, # of frees, # of block reuse, # of new block requests, # of splits, # of coalesces, # of blocks in free list, Total amount of memory, Maximum size of the heap.
>
>   - How will you update these trackers?
>
>   You can update them every time a function is called. 
>
>   - How will you report these trackers when the program ends?
>
>   We can use atexit to report the information when the program ends.
>
Response.

Demonstration
-------------

> Place a link to your demonstration slides on [Google Drive].

Errata
------

> Describe any known errors, bugs, or deviations from the requirements.

Extra Credit
------------

> Describe what extra credit (if any) that you implemented.

[Project 04]:       https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/project04.html
[CSE.30341.FA17]:   https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/
[Google Drive]:     https://drive.google.com
