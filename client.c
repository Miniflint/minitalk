/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:54:49 by trgoel            #+#    #+#             */
/*   Updated: 2024/11/11 23:54:50 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_byte(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		usleep(WAIT);
	}
}

void	get_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_pid != info->si_pid)
		return ;
	if (sig == SIGUSR1)
	{
		ft_putstr("Message sent successfully\n");
		exit(0);
	}
	if (sig == SIGUSR2)
	{
		ft_putstr("Message sending fail\n");
		exit(1);
	}
}

void	send_null(void)
{
	send_byte(g_pid, 0);
	send_byte(g_pid, 0);
	send_byte(g_pid, 0);
	send_byte(g_pid, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_signal;
	if (argc != 3)
		return (print_usage(argv[0]));
	if (!argv[2])
		return (0);
	g_pid = quick_atoi(argv[1]);
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_putstr("Signal couldn't reach destination\n");
		return (1);
	}
	while (*argv[2])
	{
		send_byte(g_pid, *argv[2]);
		argv[2]++;
	}
	send_null();
	sleep(3);
	ft_putstr("Fail to send message\n");
	return (1);
}
