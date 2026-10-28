#include "pcbmanager.h"
#include "synch.h"


PCBManager::PCBManager(int max) {

    maxProcesses = max;
    bitmap = new BitMap(maxProcesses);
    pcbs = new PCB*[maxProcesses];

    for(int i = 0; i < maxProcesses; i++) {
        pcbs[i] = NULL;
    }

	pcbManagerLock = new Lock("pcbManagerLock");

}


PCBManager::~PCBManager() {

    delete bitmap;

    delete[] pcbs;

    delete pcbManagerLock;

}


PCB* PCBManager::AllocatePCB() {

    // Acquire pcbManagerLock
    pcbManagerLock->Acquire();

    int pid = bitmap->Find();

    // Release pcbManagerLock
    pcbManagerLock->Release();

    if (pid == -1)
    {
	return NULL;
    }

    pcbs[pid] = new PCB(pid);

    return pcbs[pid];

}


int PCBManager::DeallocatePCB(PCB* pcb) {

    // Check is pcb is valid -- check pcbs for pcb->pid
    if (pcb == NULL || pcbs[pcb->pid] != pcb)
    {
	return -1;
    }

     // Aquire pcbManagerLock
     pcbManagerLock->Acquire();

    bitmap->Clear(pcb->pid);

    // Release pcbManagerLock
    pcbManagerLock->Release();

    int pid = pcb->pid;

    delete pcbs[pid];

    pcbs[pid] = NULL;

    return 0;

}

PCB* PCBManager::GetPCB(int pid) {
    return pcbs[pid];
}
