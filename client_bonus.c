#include "minitalk_bonus.h"

void	ft_sent_str_sub(pid_t pid, char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		usleep(55);
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

void	ft_sent_str(pid_t pid_s, char *s)
{
	int		i;
	pid_t	pid_c;

	i = 0;
	pid_c = getpid();
	if (pid_c <= 0)
	{
		write(1, "Error\nGet pid\n", 14);
		exit (0);
	}
	while (s[i] != '\0')
		ft_sent_str_sub(pid_s, s[i++]);
	ft_sent_str_sub(pid_s, s[i++]);
	while (pid_c > 0)
	{
		i = pid_c % 10 + '0';
		ft_sent_str_sub(pid_s, i);
		pid_c = pid_c / 10;
	}
	ft_sent_str_sub(pid_s, EOT);
	return ;
}

void	ft_finish(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "\x1b[35mmessege correctly sent\x1b[39m\n", 33);
		exit(0);
	}
}

void	ft_client(char **argv)
{
	pid_t	*pid;

	pid = (pid_t *)ft_myatoi(argv[1]);
	if (pid == NULL || kill(*pid, 0) == -1)
	{
		write(2, "PID error\n", 10);
		exit(0);
	}
	ft_sent_str(*pid, argv[2]);
	free(pid);
	if (signal(SIGUSR1, ft_finish) == SIG_ERR)
		exit(0);
	while (1)
	{
	}
	return ;
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		ft_client(argv);
	else
		write(2, "Error\nArguments have to be three.\n", 34);
	return (0);
}
