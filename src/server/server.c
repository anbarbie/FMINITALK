/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:09:21 by antbarbi          #+#    #+#             */
/*   Updated: 2021/09/20 20:24:13 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_buff	g_s;

static	void	print_pid(void)
{
	ft_putstr_fd("PID = ", 1);
	ft_putnbr_fd((int)getpid(), 1);
	ft_putstr_fd("\n", 1);
}

static	void	reset_struct(void)
{
	if (g_s.cpt != BUFFER)
		ft_putchar_fd('\n', 1);
	ft_bzero(g_s.str, g_s.cpt);
	g_s.cpt = 0;
}

static	void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	tmp = 0;

	(void)context;
	if (signum == SIGUSR2)
		tmp |= 1;
	if (i == 7)
	{
		g_s.str[g_s.cpt] = tmp;
		i = -1;
		g_s.cpt++;
		if (g_s.cpt == BUFFER || g_s.str[g_s.cpt - 1] == '\0')
		{
			tmp = 0;
			write(1, &g_s.str, g_s.cpt);
			kill(info->si_pid, SIGUSR1);
			reset_struct();
		}
	}
	tmp <<= 1;
	i++;
}

int	main(void)
{	
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	g_s.cpt = 0;
	ft_memset(g_s.str, 0, BUFFER);
	print_pid();
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
