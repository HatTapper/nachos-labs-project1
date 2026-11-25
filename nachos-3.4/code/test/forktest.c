#include "syscall.h"

void child()
{
    Yield();
    Exit(7);
}

void killme()
{
    Yield();
    Yield();
    Exit(9);
}

void execer()
{
    Exec("../test/exit3");
    Exit(1);
}

void shortchild()
{
    Yield();
    Exit(1);
}

int main()
{
    int pid;
    int status;
    int pids[8];
    int n;
    int i;

    pid = Fork(child);
    status = Join(pid);

    pid = Fork(killme);
    Kill(pid);
    status = Join(pid);

    status = Join(99);
    Kill(99);

    pid = Fork(execer);
    status = Join(pid);

    n = 0;
    while (n < 8)
    {
        pid = Fork(shortchild);
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