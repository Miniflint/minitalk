#include "minitalk.h"

void	send_byte(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c & 1) == 0)
		{
			u_putnbr(0);
			kill(pid, SIGUSR1);
		}
		else if ((c & 1) == 1)
		{
			u_putnbr(1);
			kill(pid, SIGUSR2);
		}
		c = c >> 1;
		i++;
		write(1, "\n", 1);
		usleep(200000);
	}
}


int	main(int argc, char **argv)
{
	char	*s;
	int		at_rtn;

	if (argc != 3)
		return (print_usage(argv[0]));
	s = argv[2];
	if (!s)
		return (0);
	at_rtn = quick_atoi(argv[1]);
	while (*s)
	{
		send_byte(at_rtn, *s);
		s++;
	}
	return (0);
}
