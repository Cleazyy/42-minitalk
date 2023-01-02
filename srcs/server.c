/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 07:41:58 by fluchten          #+#    #+#             */
/*   Updated: 2022/12/29 10:38:28 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_print_pid(pid_t pid)
{
	ft_putstr_fd("PID = ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

static void	ft_handler(int signum)
{
	static int	count_bits = 0;
	static int	i = 0;

	if (signum == SIGUSR1)
	{
		i |= (1 << count_bits);
		count_bits++;
	}
	else if (signum == SIGUSR2)
		count_bits++;
	if (count_bits == 8)
	{
		write(1, &i, 1);
		count_bits = 0;
		i = 0;
	}
}

int	main(void)
{
	ft_print_pid(getpid());
	while (1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause();
	}
	return (0);
}
