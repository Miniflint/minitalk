#include "minitalk.h"



int	main(void)
{
	const int	pid = getpid();

	u_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		;
}
