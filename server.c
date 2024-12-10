/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:32:18 by mohel-am          #+#    #+#             */
/*   Updated: 2024/12/10 05:09:51 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

void	convert_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	tmp;
	static int				index;

	tmp |= (signal == SIGUSR1);
	index++;
	if (index == 8)
	{
		if (tmp == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", tmp);
		index = 0;
		tmp = 0;
	}
	else
		tmp <<= 1;
	if (signal == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signal == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
	(void)context;
}

int	main(void)
{
	struct sigaction	minitalk;

	minitalk.sa_sigaction = &convert_signal;
	minitalk.sa_flags = SA_SIGINFO;
	sigemptyset(&minitalk.sa_mask);
	ft_printf("server_pid --> %d\n", getpid());
	sigaction(SIGUSR1, &minitalk, NULL);
	sigaction(SIGUSR2, &minitalk, NULL);
	while (1)
		pause();
	return (0);
}
