/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:13:40 by mohel-am          #+#    #+#             */
/*   Updated: 2024/12/10 05:11:34 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

void	receive_from_server(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Received: 1\n");
	else if (signal == SIGUSR2)
		ft_printf("Received: 0\n");
}

void	send_signal(int server_pid, unsigned char c)
{
	unsigned char	tmp;
	int				i;

	i = 8;
	while (i > 0)
	{
		i--;
		tmp = c >> i;
		if (tmp % 2 == 0)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(500);
	}
}

int	check_pid(char *str)
{
	int	pid;

	pid = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			ft_printf("Invalid PID\n");
			return (-1);
		}
		pid = pid * 10 + (*str - '0');
		str++;
	}
	return (pid);
}

int	main(int ac, char **av)
{
	int				server_pid;
	unsigned char	*str;

	signal(SIGUSR1, receive_from_server);
	signal(SIGUSR2, receive_from_server);
	if (ac == 3)
	{
		server_pid = check_pid(av[1]);
		str = (unsigned char *)av[2];
		while (*str)
			send_signal(server_pid, *str++);
		send_signal(server_pid, '\0');
	}
	else
		ft_printf("Usage : %s <server pid> <massage>", av[0]);
}
