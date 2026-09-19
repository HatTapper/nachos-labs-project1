// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "synch.h"

// testnum is set in main.cc
int testnum = 1;



//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------
int SharedVariable;

#ifdef HW1_SEMAPHORES
int numThreadsActive;
Semaphore *mutex = new Semaphore("mutex", 1);
Semaphore *barrier = new Semaphore("barrier", 0);
int arrivedCount = 0;
#endif

void
SimpleThread(int which)
{
    int num, val;

    for (num = 0; num < 5; num++) {
#ifdef HW1_SEMAPHORES
        mutex->P();
        val = SharedVariable;
        printf("*** thread %d sees value %d\n", which, val);
        SharedVariable = val + 1;
        mutex->V();
        currentThread->Yield();
#else
        val = SharedVariable;
        printf("*** thread %d sees value %d\n", which, val);
        currentThread->Yield();
        SharedVariable = val + 1;
        currentThread->Yield();
#endif
    }

#ifdef HW1_SEMAPHORES
    mutex->P();
    arrivedCount++;
    if (arrivedCount == numThreadsActive) {
        for (int i = 0; i < numThreadsActive; i++)
            barrier->V();
    }
    mutex->V();
    barrier->P();
#endif

    val = SharedVariable;
    printf("Thread %d sees final value %d\n", which, val);
}

//----------------------------------------------------------------------
// ThreadTest
//----------------------------------------------------------------------

void
ThreadTest(int n)
{
    DEBUG('t', "Entering ThreadTest");
    Thread *t;
#ifdef HW1_SEMAPHORES
    numThreadsActive = n;
#endif
    if (n > 0)
    {
	for(int i = 1; i < n; i++)
	{
		t = new Thread("forked thread");
		t->Fork (SimpleThread, i);
	}

        SimpleThread(0);
    }

}

