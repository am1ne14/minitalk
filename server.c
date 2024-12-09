/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-am <mohel-am@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:32:18 by mohel-am          #+#    #+#             */
/*   Updated: 2024/12/09 22:06:59 by mohel-am         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf/ft_printf.h"

void	convert_signal(int signal)
{
	static int	index;
	static unsigned char	tmp;

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
}

int main()
{
	ft_printf("server_pid : %d\n", getpid());
	signal(SIGUSR1, convert_signal);
	signal(SIGUSR2, convert_signal);
	while (1)
		pause();
	return (0);
}
