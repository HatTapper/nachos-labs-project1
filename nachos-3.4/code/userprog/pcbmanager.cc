#include "pcbmanager.h"
#include "synch.h"

PCBManager::PCBManager(int max)
{

    maxProcesses = max;
    bitmap = new BitMap(maxProcesses);
    pcbs = new PCB *[maxProcesses];

    for (int i = 0; i < maxProcesses; i++)
    {
        pcbs[i] = NULL;
    }

    pcbManagerLock = new Lock("pcbManagerLock");
}

PCBManager::~PCBManager()
{

    delete bitmap;

    delete[] pcbs;

    delete pcbManagerLock;
}

PCB *PCBManager::AllocatePCB()
{

    // Acquire pcbManagerLock
    pcbManagerLock->Acquire();

    int pid = bitmap->Find();
    PCB *pcb = NULL;

    if (pid != -1)
    {
        pcb = new PCB(pid);
        pcbs[pid] = pcb;
    }

    // Release pcbManagerLock
    pcbManagerLock->Release();

    return pcb;
}

int PCBManager::DeallocatePCB(PCB *pcb)
{
    if (pcb == NULL)
    {
        return -1;
    }

    // Aquire pcbManagerLock
    pcbManagerLock->Acquire();

    // Check is pcb is valid -- check pcbs for pcb->pid
    int pid = pcb->pid;
    if (pid < 0 || pid >= maxProcesses || pcbs[pid] != pcb)
    {
        pcbManagerLock->Release();
        return -1;
    }

    pcbs[pid] = NULL;
    bitmap->Clear(pcb->pid);

    // Release pcbManagerLock
    pcbManagerLock->Release();

    // unreachable from the table, so all good to delete outside the lock
    delete pcb;

    return 0;
}

PCB *PCBManager::GetPCB(int pid)
{
    if (pid < 0 || pid >= maxProcesses)
    {
        return NULL;
    }

    return pcbs[pid];
}
