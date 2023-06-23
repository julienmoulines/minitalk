#include "minitalk.h"

int	main(void)
{
  while (1)
  {
	  struct sigaction	sa;

	  printf("PID du serveur : %d\n", getpid());
	
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &count_g_len;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1
		  || sigaction(SIGUSR2, &sa, NULL) == -1)
		  exit(1);
		while (1)
			usleep(1);
  }
	return (0);
}