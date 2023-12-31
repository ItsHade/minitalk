/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:28:32 by maburnet          #+#    #+#             */
/*   Updated: 2023/07/11 17:31:19 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_handle_sigusr(int signum, siginfo_t *info, void *ptr)
{
	static unsigned int 	c = 0;
	static int				i = 0;

	(void) ptr;
	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		ft_putchar(c);
		c = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

void	ft_server(void)
{
	ft_putstr("pid: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void) argv;
	sa.sa_sigaction = &ft_handle_sigusr;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (argc != 1)
	{
		ft_putstr("Arguments pas valides\n");
		return (0);
	}
	ft_server();
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
