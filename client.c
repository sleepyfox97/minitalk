#include "minitalk.h"

void	ft_sent_str_sub(pid_t pid, char c)
{
	int i;
	int bit;

	i = 0;
	while (i < 8)
	{
		usleep(500);
		bit = (c >> i) & 1;
		if (bit == 1)
			bit = kill(pid, SIGUSR1);
		else
			bit = kill(pid, SIGUSR2);
		if (bit == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	return ;
}

void ft_sent_str(pid_t pid, char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		ft_sent_str_sub(pid, s[i++]);
	i = -1;
	while (++i < 8)
	{
		usleep(500);
		if (kill(pid, SIGUSR2) < 0)
			exit(EXIT_FAILURE);
	}
	return ;
}

void	ft_client(char **argv)
{
	pid_t	*pid;

	pid = (pid_t *)ft_myatoi(argv[1]);
	if (pid == NULL || kill(*pid, 0) == -1)
	{
		write(2, "PID error\n",10);
		exit(0);
	}
	ft_sent_str(*pid, argv[2]);
	free(pid);
	return ;
}

int main(int argc, char *argv[])
{
	if (argc == 3)
		ft_client(argv);
	else
		write(2, "Error\nArguments have to be three.\n", 34);
	return (0);
}
