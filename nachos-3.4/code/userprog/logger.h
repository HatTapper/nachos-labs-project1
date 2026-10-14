#ifndef LOGGER_H
#define LOGGER_H

#include "copyright.h"

class Logger
{
public:
    static void LogSyscall(int pid, const char *syscall);
    static void LogLoadedProgram(int code, int data, int bss);
    static void LogFork(int pid, int addr, int numPages);
    static void LogExec(int pid, const char *name);
    static void LogExit(int pid, int status);
    static void LogKill(int pid, int killedPid, bool success);
};

#endif