#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# define MSG_SIZE 100
# define WAIT 50

pid_t	g_pid;

typedef struct s_msg
{
	pid_t	pid;
	char	*mess;
	int		mess_len;
	int		index;
}	t_msg;

int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		quick_atoi(char *str);
void	u_putnbr(unsigned int n);
int		print_usage(char *prog_name);

#endif
