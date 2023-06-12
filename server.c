#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

sig_atomic_t	g_len = 0;

int ft_end(siginfo_t *info, unsigned char **str)
{
    kill(info->si_pid, SIGUSR2);
    printf("Message transmis : %s\n\n", *str);
    g_len = 0;
    free(*str);
    *str = NULL;
    return 0;
}

void admin(int sig, siginfo_t *info, void *context)
{
    static unsigned char byte = 0;
    static int count = 0;
    static unsigned char *str;
    static size_t i = 0;
    static int mask = 1 << 7; // Masque initial

    if (!str)
        str = calloc(g_len + 1, sizeof(unsigned char));

    if (sig == SIGUSR1)
        byte |= mask;

    mask >>= 1; // Décalage du masque

    if (mask == 0)
    {
        str[i] = byte;
        count = 0;
        byte = 0;
        mask = 1 << 7; // Réinitialisation du masque
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


void	count_g_len(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR1)
	{
		g_len++;
	}
	else if (sig == SIGUSR2)
	{
		g_len = g_len * -1;
	}
}

int	main(void)
{
	struct sigaction	sa;

	printf("PID du serveur : %d\n", getpid());
	while (1)
	{
		memset(&sa, 0, sizeof(struct sigaction));
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = count_g_len;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		while (g_len >= 0)
			pause();
		g_len *= -1;
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = admin;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		while (g_len != 0)
			pause();
	}
	return (0);
}
