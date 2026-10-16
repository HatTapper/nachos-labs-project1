#include "copyright.h"
#include "system.h"
#include "machine.h"
#include "memorymanager.h"

void MemoryManagerTest()
{
    int frames[NumPhysPages];
    int i;

    printf("MemoryManager test: free = %d (expect %d)\n",
           mm->GetFreePageCount(), NumPhysPages);

    // allocate everything
    for (i = 0; i < NumPhysPages; i++)
    {
        frames[i] = mm->AllocatePage();
        ASSERT(frames[i] != -1);
    }
    printf("after allocating all: free = %d (expect 0)\n", mm->GetFreePageCount());

    // one more must fail
    printf("33rd allocation returns %d (expect -1)\n", mm->AllocatePage());

    // free everything
    for (i = 0; i < NumPhysPages; i++)
        ASSERT(mm->DeallocatePage(frames[i]) == 0);
    printf("after freeing all: free = %d (expect %d)\n",
           mm->GetFreePageCount(), NumPhysPages);

    // double free and bad index must be rejected
    printf("double free returns %d (expect -1)\n", mm->DeallocatePage(frames[0]));
    printf("bad index returns %d (expect -1)\n", mm->DeallocatePage(NumPhysPages));
}