/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:25:51 by maburnet          #+#    #+#             */
/*   Updated: 2023/07/11 17:27:03 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	ft_sendchar(int server_id, char letter)
{
	int		c;

	c = 0;
	while (c < 8)
	{
		if ((letter & (0x01 << c)) != 0)
			kill(server_id, SIGUSR1);
		else
			kill(server_id, SIGUSR2);
		usleep(800);
		c++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	server_id;
	int i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr("Arguments invalides\n");
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
		ft_sendchar(server_id, argv[2][i]);
		i++;
	}
	ft_sendchar(server_id, '\n');
	return (0);
}
