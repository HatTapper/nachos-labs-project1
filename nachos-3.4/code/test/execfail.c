#include "syscall.h"

int main(void)
{
    int r = Exec("../test/doesnotexist");
    if (r == -1)
    {
        Halt();
    }

    return 0;
}