#include "syscall.h"

int main()
{
	int r;
	r = Join (-5);
	r = Join (50);
	Kill(50);
	Exit(r);
}
