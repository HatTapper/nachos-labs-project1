
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "copyright.h"

void Elevator(int numFloors);
void ArrivingGoingFromTo(int atFloor, int toFloor);

typedef struct Person
{
    int id;
    int atFloor;
    int toFloor;
} Person;

class ELEVATOR
{

public:
    ELEVATOR(int numFloors);
    ~ELEVATOR();
    void hailElevator(Person *p);
    void start();

private:
    int currentFloor;
    Condition **entering;
    Condition **leaving;
    Condition *hailed;
    int elevatorFloors;
    int *personsWaiting;
    int occupancy;
    int maxOccupancy;
    int direction; // +1 is going up, -1 is going down
    Lock *elevatorLock;
};

#endif