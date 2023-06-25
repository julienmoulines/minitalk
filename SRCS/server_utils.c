/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:57:47 by jmouline          #+#    #+#             */
/*   Updated: 2023/06/25 00:57:47 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

sig_atomic_t	g_len = 0;

void	count_g_len(int sig, siginfo_t *info, void *context)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	(void)context;
	if (sig == SIGUSR1)
		g_len++;
	else if (sig == SIGUSR2)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &admin;
		if (sigaction(SIGUSR1, &sa, NULL) == -1
			|| sigaction(SIGUSR2, &sa, NULL) == -1)
			exit(1);
	}
	kill(info->si_pid, SIGUSR1);
}

void	admin(int sig, siginfo_t *info, void *context)
{
	static unsigned char	byte = 0;
	static unsigned char	*str;
	static size_t			i = 0;
	static int				bit_index = 7;

	(void)context;
	if (str == NULL)
		str = malloc(sizeof(unsigned char) * g_len + 1);
	if (sig == SIGUSR1)
		byte |= (1 << bit_index);
	else if (sig == SIGUSR2)
		byte &= ~(1u << bit_index);
	bit_index--;
	if (bit_index < 0)
	{
		str[i] = byte;
		byte = 0;
		bit_index = 7;
		if (ft_end(info, &str, &i) == 1)
			return ;
		i++;
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

int	ft_end(siginfo_t *info, unsigned char **str, size_t *i)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	if ((*str)[*i] == '\0')
	{
		printf("Message transmis : %s\n\n", *str);
		kill(info->si_pid, SIGUSR2);
		g_len = 0;
		free(*str);
		*str = NULL;
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &count_g_len;
		if (sigaction(SIGUSR1, &sa, NULL) == -1
			|| sigaction(SIGUSR2, &sa, NULL) == -1)
			exit(1);
		*i = 0;
		return (1);
	}
	return (0);
}
