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

//maybe need to malloc the full char * before printing
//when running ./client multiple times fast the signals overlap 

void	ft_handle_sigusr(int signum, siginfo_t *info, void *ptr)
{
	(void) ptr;
	static unsigned int 	c = 0;
	static int				i = 0;
	if (signum == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			ft_putchar('\n');
			kill(info->si_pid, SIGUSR1);
		}
		else
			ft_putchar(c);
		c = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

void	ft_server(void)
{
	ft_putstr("Server pid: ");
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
