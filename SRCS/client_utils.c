/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:23:28 by jmouline          #+#    #+#             */
/*   Updated: 2023/06/25 02:53:20 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

sig_atomic_t	g_len = 0;

void	ft_adr(int sig, siginfo_t *sig_info, void *context)
{
	(void)sig_info;
	(void)context;
	if (sig == SIGUSR1)
		g_len = 1;
	else if (sig == SIGUSR2)
	{
		printf("La chaine a été passé au serveur avec succès.\n");
		exit(EXIT_SUCCESS);
	}
}

void	ft_len(int pid, int a_len)
{
	ft_printf("\nLa chaine compte %d caractères.\n", a_len);
	if (a_len == 0)
	{
		ft_printf("Rien à envoyer au serveur.\n");
		exit(1);
	}
	while (a_len > 0)
	{
		g_len = 0;
		kill(pid, SIGUSR1);
		a_len--;
		while (!g_len)
			usleep(1);
	}
	kill(pid, SIGUSR2);
}

void	ft_atob(int pid, char c)
{
	unsigned char	bit_cmp;
	int				mask;

	mask = 7;
	bit_cmp = 1u << mask;
	while (mask >= 0)
	{
		g_len = 0;
		if (bit_cmp & c)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_len)
			usleep(1);
		mask--;
		bit_cmp >>= 1;
	}
}

int	ft_client_end(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\0')
		{
			ft_atob(pid, '\0');
			return (1);
		}
		ft_atob(pid, str[i]);
		i++;
		if (str[i] == '\0')
		{
			ft_atob(pid, '\0');
			return (1);
		}
	}
	return (0);
}
