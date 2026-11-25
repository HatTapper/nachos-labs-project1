# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -m32 -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: create exit halt shell matmult sort exectest execfail forktest forkreturn exit3 forkexec forkloop threeproc

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

create.o: create.c
	$(CC) $(CFLAGS) -c create.c
create: create.o start.o
	$(LD) $(LDFLAGS) start.o create.o -o create.coff
	../bin/coff2noff create.coff create

exit3.o: exit3.c
	$(CC) $(CFLAGS) -c exit3.c
exit3: exit3.o start.o
	$(LD) $(LDFLAGS) start.o exit3.o -o exit3.coff
	../bin/coff2noff exit3.coff exit3

forktest.o: forktest.c
	$(CC) $(CFLAGS) -c forktest.c
forktest: forktest.o start.o
	$(LD) $(LDFLAGS) start.o forktest.o -o forktest.coff
	../bin/coff2noff forktest.coff forktest

forkreturn.o: forkreturn.c
	$(CC) $(CFLAGS) -c forkreturn.c
forkreturn: forkreturn.o start.o
	$(LD) $(LDFLAGS) start.o forkreturn.o -o forkreturn.coff
	../bin/coff2noff forkreturn.coff forkreturn

forkexec.o: forkexec.c
	$(CC) $(CFLAGS) -c forkexec.c
forkexec: forkexec.o start.o
	$(LD) $(LDFLAGS) start.o forkexec.o -o forkexec.coff
	../bin/coff2noff forkexec.coff forkexec

forkloop.o: forkloop.c
	$(CC) $(CFLAGS) -c forkloop.c
forkloop: forkloop.o start.o
	$(LD) $(LDFLAGS) start.o forkloop.o -o forkloop.coff
	../bin/coff2noff forkloop.coff forkloop

threeproc.o: threeproc.c
	$(CC) $(CFLAGS) -c threeproc.c
threeproc: threeproc.o start.o
	$(LD) $(LDFLAGS) start.o threeproc.o -o threeproc.coff
	../bin/coff2noff threeproc.coff threeproc

exit.o: exit.c
	$(CC) $(CFLAGS) -c exit.c
exit: exit.o start.o
	$(LD) $(LDFLAGS) start.o exit.o -o exit.coff
	../bin/coff2noff exit.coff exit

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

exectest.o: exectest.c
	$(CC) $(CFLAGS) -c exectest.c
exectest: exectest.o start.o
	$(LD) $(LDFLAGS) start.o exectest.o -o exectest.coff
	../bin/coff2noff exectest.coff exectest

execfail.o: execfail.c
	$(CC) $(CFLAGS) -c execfail.c
execfail: execfail.o start.o
	$(LD) $(LDFLAGS) start.o execfail.o -o execfail.coff
	../bin/coff2noff execfail.coff execfail
jointest.o: jointest.c
	$(CC) $(CFLAGS) -c jointest.c
jointest: jointest.o start.o
	$(LD) $(LDFLAGS) start.o jointest.o -o jointest.coff
	../bin/coff2noff jointest.coff jointest

killself.o: killself.c
	$(CC) $(CFLAGS) -c killself.c
killself: killself.o start.o
	$(LD) $(LDFLAGS) start.o killself.o -o killself.coff
	../bin/coff2noff killself.coff killself

