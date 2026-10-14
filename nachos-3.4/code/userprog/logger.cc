#include "copyright.h"
#include "utility.h"
#include "logger.h"

void Logger::LogSyscall(int pid, const char *syscall)
{
    printf("System Call: %d invoked %s\n", pid, syscall);
}
void Logger::LogLoadedProgram(int code, int data, int bss)
{
    printf("Loaded Program: %d code | %d data | %d bss\n", code, data, bss);
}
void Logger::LogFork(int pid, int addr, int numPages)
{
    printf("Process %d Fork: start at address 0x%x with %d pages memory\n", pid, addr, numPages);
}
void Logger::LogExec(int pid, const char *name)
{
    printf("Exec Program: %d loading %s\n", pid, name);
}
void Logger::LogExit(int pid, int status)
{
    printf("Process %d exits with %d\n", pid, status);
}
void Logger::LogKill(int pid, int killedPid, bool success)
{
    if (success)
    {
        printf("Process %d killed process %d\n", pid, killedPid);
    }
    else
    {
        printf("Process %d cannot kill process %d: doesn't exist\n", pid, killedPid);
    }
}