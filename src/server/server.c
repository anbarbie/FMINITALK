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

static	void	print_pid(void)
{
	ft_putstr_fd("PID = ", 1);
	ft_putnbr_fd((int)getpid(), 1);
	ft_putstr_fd("\n", 1);
}

static	void	reset_struct(t_buff *s)
{
	if (s->cpt != BUFFER)
		ft_putchar_fd('\n', 1);
	ft_bzero(s->str, s->cpt);
	s->cpt = 0;
}

static	void	sig_handler(int signum)
{
	static int				i = 0;
	static unsigned char	tmp = 0;
	static t_buff			s = {};

	if (signum == SIGUSR2)
		tmp |= 1;
	if (i == 7)
	{
		s.str[s.cpt] = tmp;
		i = -1;
		s.cpt++;
		if (s.cpt == BUFFER || s.str[s.cpt - 1] == '\0')
		{
			tmp = 0;
			write(1, &s.str, s.cpt);
			reset_struct(&s);
		}
	}
	tmp <<= 1;
	i++;
}

int	main(void)
{	
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	print_pid();
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
