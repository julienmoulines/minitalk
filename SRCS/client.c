/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:57:33 by jmouline          #+#    #+#             */
/*   Updated: 2023/06/25 00:57:33 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = &ft_adr;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
	{
		ft_printf("Mauvais arguments\nVeuillez entrer : %s PID MESSAGE\n", av[0]);
		return (1);
	}
	pid = ft_atoi(av[1]);
	ft_len(pid, ft_strlen(av[2]));
	usleep(500);
	if (ft_client_end(pid, av[2]) == 1)
		return (0);
	else
		ft_printf("Erreur transmission\n");
	return (1);
}
