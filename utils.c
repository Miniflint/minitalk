/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:54:56 by trgoel            #+#    #+#             */
/*   Updated: 2024/11/11 23:54:58 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	u_putnbr(unsigned int n)
{
	const char	c = (n % 10) + '0';

	if (n > 9)
		u_putnbr(n / 10);
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

int	print_usage(char *prog_name)
{
	ft_putstr("Error:\n");
	ft_putstr("\tUsage: ");
	ft_putstr(prog_name);
	ft_putstr(" [pid] [string to send]\n");
	return (1);
}

int	quick_atoi(char *str)
{
	unsigned int	ret;
	int				neg;

	neg = 1;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	ret = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		ret = (ret * 10) + (*str - '0');
		str++;
	}
	return (ret);
}
