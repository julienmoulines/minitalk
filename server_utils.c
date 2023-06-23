#include "minitalk.h"

sig_atomic_t g_len = 0;

void	count_g_len(int sig, siginfo_t *info, void *context)
{
  struct sigaction	sa;

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

void admin(int sig, siginfo_t *info, void *context)
{
    static unsigned char byte = 0;
    static unsigned char *str;
    static size_t i = 0;
	  static int				bit_index = 7;

	(void)context;
  if (!str)
    str = malloc(sizeof(unsigned char) * g_len);
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
        if (str[i] == '\0')
        {
            i = ft_end(info, &str);
            return;
        }
        i++;
    }
	  usleep(50);
    kill(info->si_pid, SIGUSR1);
}

int ft_end(siginfo_t *info, unsigned char **str)
{
   struct sigaction	sa;
  
    kill(info->si_pid, SIGUSR2);
    printf("Message transmis : %s\n\n", *str);
    g_len = 0;
    free(*str);
    *str = NULL;
    sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &count_g_len;
		if (sigaction(SIGUSR1, &sa, NULL) == -1
			|| sigaction(SIGUSR2, &sa, NULL) == -1)
			exit(1);
    return 0;
}