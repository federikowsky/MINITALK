/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:11:14 by fefilipp          #+#    #+#             */
/*   Updated: 2022/03/27 15:57:15 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static pid_t	g_client_info;

static void	ft_stop_receiving(void)
{
	kill(g_client_info, SIGUSR1);
	return ;
}

static void	ft_process(int s, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 8;

	context = NULL;
	g_client_info = info->si_pid;
	c = c | (s == SIGUSR1);
	if (--i == 0)
	{
		i = 8;
		if (c == 17)
			ft_stop_receiving();
		else
			write(1, &c, 1);
		c = 0;
	}
	else
		c = c << 1;
}

	// ft_printf("Server PID: %d\n\n", getpid());

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.__sigaction_u.__sa_sigaction = ft_process;
	sa.sa_flags = SA_SIGINFO;
	printf("Server PID: %d\n\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
