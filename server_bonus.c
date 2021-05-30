#include "minitalk_bonus.h"

char	ft_putchar_sig(int bit)
{
	static int	i = 0;
	static char	c = 0;
	char		tmp;

	if (g_flag < 2)
		g_flag = 0;
	if (i < 8)
	{
		c = c + (bit << i);
		i++;
	}
	if (i == 8)
	{
		if (g_flag < 2)
			g_flag = 1;
		else if (g_flag == 2)
			g_flag = 3;
		tmp = c;
		if (c == '\0')
			g_flag = 2;
		i = 0;
		c = 0;
		return (tmp);
	}
	return (0);
}

void	ft_get_char(int sig)
{
	char		c;
	static char	s[101] = {};
	static int	i = 0;

	if (g_flag < 2)
	{
		if (sig == SIGUSR1)
			c = ft_putchar_sig(1);
		else if (sig == SIGUSR2)
			c = ft_putchar_sig(0);
		if (g_flag == 1 || g_flag == 2)
		{
			s[i] = c;
			i++;
			if (g_flag == 2 || i == 100)
			{
				s[100] = '\0';
				ft_putstr_fd(s, 1);
				i = 0;
			}
		}
	}
	else
		ft_get_pid(sig);
	return ;
}

void	ft_get_pid(int sig)
{
	char		c;
	static int	pid = 0;
	static int	i = 1;

	if (sig == SIGUSR1)
		c = ft_putchar_sig(1);
	else if (sig == SIGUSR2)
		c = ft_putchar_sig(0);
	if (g_flag == 3)
	{
		g_flag = 2;
		if (c != EOT)
			pid = (c - '0') * i + pid;
		i = i * 10;
		if (c == EOT)
		{
			usleep(50);
			if (kill(pid, SIGUSR1) < 0)
				exit(0);
			pid = 0;
			i = 1;
			g_flag = 0;
		}
	}		
}

void	ft_server(void)
{
	if (signal(SIGUSR1, ft_get_char) == SIG_ERR)
		exit (0);
	else if (signal(SIGUSR2, ft_get_char) == SIG_ERR)
		exit (0);
	return ;
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
		return (write(1, "Error\nArguments have to be only one.\n", 36));
	pid = getpid();
	g_flag = 0;
	if (pid <= 0)
	{
		write(1, "Error\nCan't get pid\n", 20);
		exit (0);
	}
	write(1, "pid=", 4);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	ft_server();
	while (1)
	{
	}
}
