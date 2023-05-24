#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int len = 0;

void admin(int sig, siginfo_t *info, void *context)
{
    static unsigned char byte = 0;
    static int count = 0;
    static unsigned char *str;
    static size_t i = 0;

	usleep(500);
    if (!str)
        str = calloc(len + 1, sizeof(unsigned char));

    if (sig == SIGUSR1)
        byte |= (1 << (7 - count));
    count++;
    if (count == 8)
    {
        str[i] = byte;
        count = 0;
        byte = 0;
        if (str[i] == '\0')
        {
            kill(info->si_pid, SIGUSR2);
            printf("Message transmis : %s\n", str);
            free(str);
			str = NULL;
			len = 0;
			i = 0;
			return;
        }
        i++;
    }
    kill(info->si_pid, SIGUSR1);
}


void count_len(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1)
    {
        len++;
    }     
    else if (sig == SIGUSR2)
    {
        len = len * -1;
    }
}

int main()
{
    struct sigaction sa;
    
    int pid = getpid();
    printf("PID du serveur : %d\n", pid);

	while (1)
	{
		memset(&sa, 0, sizeof(struct sigaction));
    	sa.sa_flags = SA_SIGINFO;
    	sigaction(SIGUSR1, &sa, NULL);
    	sigaction(SIGUSR2, &sa, NULL);
		memset(&sa, 0, sizeof(struct sigaction));
    	sa.sa_handler = SIG_DFL;
    	sa.sa_flags = SA_SIGINFO;
   		sa.sa_sigaction = count_len;
    	sigaction(SIGUSR1, &sa, NULL);
    	sigaction(SIGUSR2, &sa, NULL);
		while (len >= 0)
       		pause();
    	len *= -1;
   		memset(&sa, 0, sizeof(struct sigaction));
    	sa.sa_flags = SA_SIGINFO;
    	sa.sa_sigaction = admin;
    	sigaction(SIGUSR1, &sa, NULL);
    	sigaction(SIGUSR2, &sa, NULL);
    	while (len != 0)
       	 pause();
	}

    return 0;
}
