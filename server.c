/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:54:44 by trgoel            #+#    #+#             */
/*   Updated: 2024/11/11 23:54:45 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static t_msg	*__set_msg(t_msg *new_msg)
{
	static t_msg	*msg;

	if (new_msg)
		msg = new_msg;
	return (msg);
}

void	expend_message(t_msg *msg)
{
	int		i;
	char	*tmp;

	tmp = msg->mess;
	msg->mess = malloc(sizeof(char) * (msg->mess_len + MSG_SIZE));
	if (!msg->mess)
	{
		kill(msg->pid, SIGUSR2);
		ft_putstr("Could not allocate malloc\n");
		exit(0);
	}
	if (!tmp)
		return ;
	i = -1;
	while (++i < msg->mess_len)
		msg->mess[i] = tmp[i];
	msg->mess[i] = 0;
	free(tmp);
}

void	next_char(t_msg *msg)
{
	msg->index = 0;
	if (msg->mess_len > 2 && !msg->mess[msg->mess_len]
		&& !msg->mess[msg->mess_len - 1]
		&& !msg->mess[msg->mess_len - 2]
		&& !msg->mess[msg->mess_len - 3])
	{
		write(1, msg->mess, msg->mess_len - 3);
		write(1, "\n", 1);
		kill(msg->pid, SIGUSR1);
		msg->mess_len = 0;
		msg->pid = 0;
		free(msg->mess);
		msg->mess = NULL;
		return ;
	}
	msg->mess_len += 1;
	if (msg->mess_len && !(msg->mess_len % MSG_SIZE))
		expend_message(msg);
	msg->mess[msg->mess_len] = 0;
}

void	get_signal(int sig, siginfo_t *info, void *context)
{
	t_msg	*msg;

	(void)context;
	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	msg = __set_msg(NULL);
	if (!msg->pid)
	{
		msg->pid = info->si_pid;
		msg->mess_len = 0;
		expend_message(msg);
		msg->mess[0] = 0;
	}
	else if (msg->pid != info->si_pid)
		return ;
	if (sig == SIGUSR2)
		msg->mess[msg->mess_len] |= 1 << msg->index;
	msg->index += 1;
	if (msg->index == 8)
		next_char(msg);
}

int	main(void)
{
	const int			pid = getpid();
	struct sigaction	sa;
	t_msg				msg;

	msg.pid = 0;
	msg.mess = NULL;
	msg.index = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_signal;
	__set_msg(&msg);
	u_putnbr(pid);
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_putstr("Signal couldn't reach destination\n");
		return (1);
	}
	while (1)
		;
	if (msg.mess)
		free(msg.mess);
	return (0);
}
