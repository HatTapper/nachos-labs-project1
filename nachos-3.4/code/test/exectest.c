#include "syscall.h"

int main(void)
{
    Exec("../test/halt");
    Halt();

    return 0;
}