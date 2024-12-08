/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:13:40 by mohel-am          #+#    #+#             */
/*   Updated: 2024/12/07 20:40:31 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	send_signal(int server_pid, unsigned char c)
{
	int	i;
	unsigned char	tmp;

	i = 8;
	while (i > 0)
	{
		i--;
		tmp = c >> i;
		if (tmp % 2 == 0)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
	}
}

int main(int ac, char **av)
{
	int	server_pid;
	unsigned char	*str;

	if (ac == 3)
	{
		server_pid = atoi(av[1]);
		str = av[2];
		while (*str)
			send_signal(server_pid, *str++);
		send_signal(server_pid, '\0');
	}
	else
		printf("Usage : %s <server pid> <massage>", av[0]);
}
