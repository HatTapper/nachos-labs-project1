#include "syscall.h"

void child()
{
    Yield();
    Exit(7);
}

void yielder()
{
    int i;
    for (i = 0; i < 5; i++)
        Yield();
    Exit(5);
}

void execer()
{
    Exec("../test/exit3");
    Exit(1);
}

int main()
{
    int pid;
    int pids[3];
    int n;
    int i;

    pid = Fork(child);
    Join(pid);

    pid = Fork(child);
    Kill(pid);
    Join(pid);

    pid = Fork(yielder);
    for (i = 0; i < 5; i++)
        Yield();
    Join(pid);

    pid = Fork(execer);
    Join(pid);

    n = 0;
    while (n < 3)
    {
        pid = Fork(child);
        if (pid == -1)
            break;
        pids[n] = pid;
        n++;
    }
    for (i = 0; i < n; i++)
        Join(pids[i]);

    Exit(0);
    return 0;
}