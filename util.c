#include "minitalk.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return ;
}

int	*ft_myatoi(char *str)
{
	long long	result;
	int			*re;

	re = (int *)malloc(sizeof(int));
	if (re == NULL)
		return (NULL);
	result = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (result > INT_MAX)
			return (NULL);
		result = ((*str++) - '0') + result * 10;
	}
	if ((*str < '0' || '9' < *str) && *str != '\0')
		return (NULL);
	*re = (int)(result);
	return (re);
}
