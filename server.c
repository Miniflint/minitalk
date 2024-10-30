#include "minitalk.h"

void	sig_handle(int sig)
{
	static unsigned char	c = 0;
	static int		i = 0;
	int		i2;
	unsigned char	c2;

//	if (sig == SIGUSR1)
//		u_putnbr(0);
//	else if (sig == SIGUSR2)
//		u_putnbr(1);
//	write(1, "\n", 1);
	c |= ((sig == SIGUSR2) << i);
	c2 = c;
	i2 = 0;
	while (i2 <= i)
	{
		if ((c2 & 1) == 1)
			u_putnbr(1);
		else if ((c2 & 1) == 0)
			u_putnbr(0);
		c2 = c2 >> 1;
		i2++;
	}
	write(1, "\n", 1);
	if (i++ == 8)
	{
		write(1, &c, 1);
		write(1, "\n", 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	const int	pid = getpid();

	u_putnbr(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, sig_handle);
	signal(SIGUSR2, sig_handle);
	while (1)
		pause();
}
