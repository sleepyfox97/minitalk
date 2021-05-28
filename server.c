#include "minitalk.h"

char	ft_putchar_sig(int bit)
{
	static int	i = 0;
	static char	c = 0;
	char		tmp;

	g_flag = 0;
	if (i < 8)
	{
		c = c + (bit << i);
		i++;
	}
	if (i == 8)
	{
		g_flag = 1;
		tmp = c;
		if (c == '\0')
			g_flag = 2;
		i = 0;
		c = 0;
		return (tmp);
	}
	return (0);
}

void	ft_swich(int sig)
{
	char c;
	static char s[2000] = {};
	static int	i=0;

	if (sig == SIGUSR1)
		c = ft_putchar_sig(1);
	else if (sig == SIGUSR2)
		c = ft_putchar_sig(0);
	if (g_flag  == 1 || g_flag == 2)
	{
		s[i] = c;
		i++;
		if (g_flag == 2 || i == 2000)
		{
			ft_putstr_fd(s, 0);
			i = 0;
		}
	}
	return ;
}

void	ft_server(void)
{
	signal(SIGUSR1, ft_swich);
	signal(SIGUSR2, ft_swich);
	return ;
}

int main()
{
	pid_t pid;

	pid = getpid();
	printf("pid=%d\n", pid);
	ft_server();
	while(1);
}
