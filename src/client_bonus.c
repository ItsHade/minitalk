/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:24:43 by maburnet          #+#    #+#             */
/*   Updated: 2023/07/11 17:25:43 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int g_countBitReceived = 0;

int	ft_sendchar(int server_id, char letter)
{
	int		c;

	c = 0;
	while (c < 8)
	{
		if (g_countBitReceived != c)
			pause();
		if ((letter & (1 << c)))
			kill(server_id, SIGUSR1);
		else
			kill(server_id, SIGUSR2);
		c++;
	}
	return (0);
}

void	ft_handlesig(int signum)
{
	if(signum == SIGUSR1)
		ft_putstr("Le message a ete recu avec succes!\n");
	else if (signum == SIGUSR2)
		g_countBitReceived += 1;
	if (g_countBitReceived > 7)
		g_countBitReceived = 0;
}

int	main(int argc, char **argv)
{
	int	server_id;
	int i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr("Arguments invalides\n");
		ft_putstr("Format: ./client_bonus [pid] [message]\n");
		return (0);
	}
	if (ft_atoi(argv[1], &server_id) == -1)
	{
		ft_putstr("pid invalide\n");
		return (-1);
	}
	if (server_id < 1 || kill(server_id, 0) == -1)
	{
		ft_putstr("pid invalide\n");
		return (-1);
	}
	while (argv[2][i])
	{
		signal(SIGUSR1, ft_handlesig);
		signal(SIGUSR2, ft_handlesig);
		ft_sendchar(server_id, argv[2][i]);
		i++;
	}
	ft_sendchar(server_id, '\0');
	return(0);
}