#ifndef MINITALK_H
# define MINITALK_H
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

//only used in server.c
int 	g_flag;

//in util.c
int		*ft_myatoi(char *str);
void	ft_putstr_fd(char *s, int fd);

//in client.c
void	ft_sent_str_sub(pid_t pid, char c);
void 	ft_sent_str(pid_t pid, char *s);
void	ft_client(char **argv);

//in server.c
char	ft_putchar_sig(int bit);
void	ft_swich(int sig);
void	ft_server(void);

#endif