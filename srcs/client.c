/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 08:50:38 by fluchten          #+#    #+#             */
/*   Updated: 2023/01/02 08:28:51 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_check_args(int ac, char **av)
{
	size_t	i;

	if (ac != 3)
		return (0);
	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_send_char(pid_t pid, char c)
{
	int	i;
	int	res;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
			ft_print_error("ERROR = Check if PID number is correct!\n");
		usleep(50);
		i++;
	}
}

static void	ft_send_str(pid_t pid, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_send_char(pid, str[i]);
		i++;
	}
	ft_send_char(pid, '\0');
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (!ft_check_args(ac, av))
		ft_print_error("ERROR = Invalid arguments!\n");
	pid = (pid_t)ft_atoi(av[1]);
	if (!pid)
		ft_print_error("ERROR = PID is NULL!\n");
	ft_send_str(pid, av[2]);
	return (0);
}
