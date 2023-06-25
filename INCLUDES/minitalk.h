/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:58:08 by jmouline          #+#    #+#             */
/*   Updated: 2023/06/25 02:19:33 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <pthread.h>
# include "../libft/libft.h"

void	count_g_len(int sig, siginfo_t *info, void *context);
void	admin(int sig, siginfo_t *info, void *context);
int		ft_end(siginfo_t *info, unsigned char **str, size_t *i);
void	ft_adr(int sig, siginfo_t *sig_info, void *context);
void	ft_len(int pid, int a_len);
void	ft_atob(int pid, char c);
int		ft_client_end(int pid, char *str);

#endif