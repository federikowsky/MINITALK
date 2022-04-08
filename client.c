/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:11:19 by fefilipp          #+#    #+#             */
/*   Updated: 2022/03/27 15:59:05 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_bits(int pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

static void	ft_str_analyse(int pid, char *s)
{
	char	c;

	while (*s)
	{
		ft_send_bits(pid, *s++);
		usleep(100);
	}
	c = 17;
	ft_send_bits(pid, c);
}

void	ft_ok_ko_received(int s)
{
	if (s == SIGUSR1)
		write(1, "\nOK\n\n", 5);
	else
		write(1, "\nKO\n\n", 5);
	exit(0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		printf("Not Enough Arguments... Stop");
		return (0);
	}
	signal(SIGUSR1, ft_ok_ko_received);
	signal(SIGUSR2, ft_ok_ko_received);
	pid = atoi(argv[2]);
	ft_str_analyse(pid, argv[1]);
	pause();
	return (0);
}
