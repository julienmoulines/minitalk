/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:57:51 by jmouline          #+#    #+#             */
/*   Updated: 2023/06/25 00:57:51 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"
#include <signal.h>

int	main(void)
{
	struct sigaction	sa;

	while (1)
	{
		ft_printf("PID du serveur : %d\n", getpid());
		sa.sa_sigaction = &count_g_len;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		if (sigaction(SIGUSR1, &sa, NULL) == -1
			|| sigaction(SIGUSR2, &sa, NULL) == -1)
			exit(1);
		while (1)
			usleep(1);
	}
	return (0);
}
