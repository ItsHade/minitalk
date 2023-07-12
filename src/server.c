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

// int g_clientpid = -1;

void	ft_handle_sigusr(int signum)
{
	static unsigned int 	c = 0;
	static int				i = 0;
	if (signum == SIGUSR1)
		i |= (0x01 << c);
	c++;
	if (c == 8)
	{
		ft_putchar(i);
		c = 0;
		i = 0;
	}
}

void	ft_server(void)
{
	ft_putstr("pid: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
}

// without the sa.sa_flags = 0; --> User defined signal ..

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = ft_handle_sigusr;
	sa.sa_flags = 0;
	(void) argv;
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
