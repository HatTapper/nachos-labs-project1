#include "pcb.h"

PCB::PCB(int id)
{

    pid = id;
    parent = NULL;
    children = new List();
    thread = NULL;
    exitStatus = 0;
    exited = false;
}

PCB::~PCB()
{

    delete children;
}

void PCB::AddChild(PCB *pcb)
{

    children->Append(pcb);
}

int PCB::RemoveChild(PCB *pcb)
{

    return children->RemoveItem(pcb);
}

bool PCB::HasExited()
{
    return exited;
}

void decspn(int arg)
{
    PCB *pcb = (PCB *)arg;
    if (pcb->HasExited())
        pcbManager->DeallocatePCB(pcb);
    else
        pcb->parent = NULL;
}

void PCB::DeleteExitedChildrenSetParentNull()
{
    children->Mapcar(decspn);
}