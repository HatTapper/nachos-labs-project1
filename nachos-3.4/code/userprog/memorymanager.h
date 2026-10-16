#ifndef MEMORY_H
#define MEMORY_H

#include "bitmap.h"

class Lock;

class MemoryManager
{

public:
    MemoryManager();
    ~MemoryManager();

    int AllocatePage();            // returns frame number, -1 if none free
    int DeallocatePage(int which); // return 0 if success, 1 if failure
    unsigned int GetFreePageCount();

private:
    BitMap *bitmap;
    Lock *lock;
};

#endif // MEMORY_H