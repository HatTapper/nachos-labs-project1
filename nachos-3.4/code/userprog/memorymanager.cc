

#include "memorymanager.h"
#include "machine.h"
#include "synch.h"

MemoryManager::MemoryManager()
{

    bitmap = new BitMap(NumPhysPages);
    lock = new Lock("MemoryManagerLock");
}

MemoryManager::~MemoryManager()
{
    delete bitmap;
    delete lock;
}

int MemoryManager::AllocatePage()
{
    lock->Acquire();
    int frame = bitmap->Find();
    lock->Release();

    return frame;
}

int MemoryManager::DeallocatePage(int which)
{
    if (which < 0 || which >= NumPhysPages)
    {
        DEBUG('a', "Invalid allocation page was requested from the Memory Manager - %d", which);
        return -1;
    }

    lock->Acquire();

    int result = -1;
    if (bitmap->Test(which))
    {
        bitmap->Clear(which);
        result = 0;
    }

    lock->Release();

    if (result == -1)
    {
        DEBUG('a', "Memory Manager dropped request to free an already freed frame. - %d", which);
    }

    return result;
}

unsigned int MemoryManager::GetFreePageCount()
{
    lock->Acquire();
    unsigned int count = bitmap->NumClear();
    lock->Release();

    return count;
}
