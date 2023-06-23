#ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include "libft/libft.h"


void	count_g_len(int sig, siginfo_t *info, void *context);
void 	admin(int sig, siginfo_t *info, void *context);
int 	ft_end(siginfo_t *info, unsigned char **str);
void	ft_adr(int sig, siginfo_t *sig_info, void *context);
void 	ft_len(int pid, int a_len);
void 	ft_atob(int pid, char c);

#endif