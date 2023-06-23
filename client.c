#include "minitalk.h"

sig_atomic_t len = 0;

void	ft_adr(int sig, siginfo_t *sig_info, void *context)
{
	(void)sig_info;
	(void)context;
	if (sig == SIGUSR1)
		len = 1;
	else if (sig == SIGUSR2)
	{
		printf("La chaine a été passé au serveur avec succès.\n");
		exit(EXIT_SUCCESS);
	}
}

static int ft_atoi(char *str)
{
    int i;
    int sign;
    unsigned long int result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        result *= 10;
        result += str[i] - '0';
        i++;
    }
    return (result * sign);
}

void ft_len(int pid, int a_len)
{
  printf("La chaine compte %d caractères.\n", a_len);
  while (a_len > 0)
	 {
		  len = 0;
	 	  kill(pid, SIGUSR1);
		  a_len--;
		  while (!len)
			 usleep(1);
	 }
	 kill(pid, SIGUSR2);
}

void ft_atob(int pid, char c)
{
    unsigned char bit_cmp;
    int mask = 7;
    bit_cmp = 1u << mask;
   while (mask >= 0)
	{
		len = 0;
		if (bit_cmp & c)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!len)
			usleep(1);
		mask--;
		bit_cmp >>= 1;
	}
}

int main(int ac, char **av)
{
    int pid;
    long int i;
    struct sigaction sa;
  sa.sa_sigaction = &ft_adr;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
    if (ac != 3)
    {
        printf("Mauvais arguments\nVeuillez entrer : %s PID MESSAGE\n", av[0]);
        return 1;
    }
    pid = ft_atoi(av[1]);
    ft_len(pid, strlen(av[2]));
    i = 0;
    usleep(500);
    while (len >= 0)
    {
        while (av[2][i] != '\0')
        {
			if (av[2][i] == '\0')
            {
                ft_atob(pid, '\0');
                return 0;
            }
            ft_atob(pid, av[2][i]);
            i++;
            if (av[2][i] == '\0')
            {
                ft_atob(pid, '\0');
                return 0;
            }
        }
    }
    return 0;
}