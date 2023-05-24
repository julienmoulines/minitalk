#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

sig_atomic_t len = 0;

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

void ft_len(int pid)
{
    while (len > 0)
    {
        kill(pid, SIGUSR1);
        usleep(10);
        len--;
    }
    kill(pid, SIGUSR2);
}

void ft_atob(int pid, char c)
{
    int bit;
    int mask;
    static int flag = 0;

    bit = 0;
    mask = 0x80;
    while (bit < 8)
    {
        if (flag > 0)
            pause();
        if (c & mask)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        mask >>= 1;
        bit++;
        flag++;
    }
}



void adr(int sig)
{
    if (sig == SIGUSR2)
        len = -1;
}

int main(int ac, char **av)
{
    int pid;
    long int i;

    if (ac != 3)
    {
        printf("Utilisation : %s PID MESSAGE\n", av[0]);
        return 1;
    }
    pid = ft_atoi(av[1]);
    len = strlen(av[2]);
	usleep(10);
    ft_len(pid);
    signal(SIGUSR1, adr);
    signal(SIGUSR2, adr);
    i = 0;
    usleep(10);
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
