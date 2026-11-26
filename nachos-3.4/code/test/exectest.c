#include "syscall.h"

int main()
{
    int r;

    r = Exec("../test/doesnotexist");
    if (r != -1)
        Exit(99);

    Exec("../test/exit3");
    Exit(1);
    return 0;
}