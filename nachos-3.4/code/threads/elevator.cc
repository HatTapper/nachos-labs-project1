#include "copyright.h"
#include "system.h"
#include "synch.h"
#include "elevator.h"

int nextPersonID = 1;
Lock *personIDLock = new Lock("PersonIDLock");

ELEVATOR *e;

// B. While there are active persons, loop doing the following
//      0. Acquire elevatorLock
//      1. Signal persons inside elevator to get off (leaving->broadcast(elevatorLock))
//      2. Signal persons atFloor to get in, one at a time, checking occupancyLimit each time
//      2.5 Release elevatorLock
//      3. Spin for some time

void ELEVATOR::start()
{
    printf("Elevator arrives on floor %d\n", currentFloor);
    while (1)
    {

        // A. Wait until hailed
        elevatorLock->Acquire();

        // yields until there is a person waiting for the elevator or the elevator has passengers
        while (1)
        {
            bool hasActivePersons = occupancy > 0;
            for (int i = 1; i <= elevatorFloors; i++)
            {
                if (personsWaiting[i] > 0)
                {
                    hasActivePersons = true;
                    break;
                }
            }

            if (hasActivePersons)
            {
                break;
            }

            hailed->Wait(elevatorLock);
        }

        // elevator has arrived, notify occupants
        leaving[currentFloor]->Broadcast(elevatorLock);
        entering[currentFloor]->Broadcast(elevatorLock);
        elevatorLock->Release();

        // yield for 50 ticks to wait for person threads to do their thing
        for (int j = 0; j < 50; j++)
        {
            currentThread->Yield();
        }

        elevatorLock->Acquire();

        if (elevatorFloors > 1)
        {
            currentFloor += direction;

            if (currentFloor == elevatorFloors)
            {
                direction = -1;
            }
            else if (currentFloor == 1)
            {
                direction = 1;
            }
        }

        printf("Elevator arrives on floor %d\n", currentFloor);

        elevatorLock->Release();
    }
}

void ElevatorThread(int numFloors)
{
    e->start();
}

ELEVATOR::ELEVATOR(int numFloors)
{
    elevatorFloors = numFloors;
    currentFloor = 1;
    direction = 1;
    occupancy = 0;
    maxOccupancy = 5;

    entering = new Condition *[numFloors + 1];
    leaving = new Condition *[numFloors + 1];
    personsWaiting = new int[numFloors + 1];
    personsWaiting[0] = 0;

    for (int i = 1; i <= numFloors; i++)
    {
        char *name = new char[32];
        sprintf(name, "Entering %d", i);
        entering[i] = new Condition(name);

        name = new char[32];
        sprintf(name, "Leaving %d", i);
        leaving[i] = new Condition(name);

        personsWaiting[i] = 0;
    }

    elevatorLock = new Lock("ElevatorLock");
    hailed = new Condition("Hailed");
}

void Elevator(int numFloors)
{
    printf("Elevator with %d floors was created!\n", numFloors);
    e = new ELEVATOR(numFloors); // build it before any person can run
    Thread *t = new Thread("Elevator");

    t->Fork(ElevatorThread, 0);
}

void ELEVATOR::hailElevator(Person *p)
{
    // need this before modifying any shared state
    elevatorLock->Acquire();

    personsWaiting[p->atFloor]++;
    hailed->Signal(elevatorLock);

    while (currentFloor != p->atFloor || occupancy >= maxOccupancy)
    {
        entering[p->atFloor]->Wait(elevatorLock);
    }

    personsWaiting[p->atFloor]--;
    occupancy++;
    printf("Person %d got into the elevator.\n", p->id);

    while (currentFloor != p->toFloor)
    {
        leaving[p->toFloor]->Wait(elevatorLock);
    }

    occupancy--;
    printf("Person %d got out of the elevator.\n", p->id);

    elevatorLock->Release();
}

void PersonThread(int person)
{

    Person *p = (Person *)person;

    printf("Person %d wants to go from floor %d to %d\n", p->id, p->atFloor, p->toFloor);

    e->hailElevator(p);
}

int getNextPersonID()
{
    personIDLock->Acquire();

    int personID = nextPersonID;
    nextPersonID = nextPersonID + 1;

    personIDLock->Release();
    return personID;
}

void ArrivingGoingFromTo(int atFloor, int toFloor)
{

    // Create Person struct
    Person *p = new Person;
    p->id = getNextPersonID();
    p->atFloor = atFloor;
    p->toFloor = toFloor;

    // Creates Person Thread
    Thread *t = new Thread("Person " + p->id);
    t->Fork(PersonThread, (int)p);
}