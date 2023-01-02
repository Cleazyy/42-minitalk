/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:14:18 by fluchten          #+#    #+#             */
/*   Updated: 2023/01/02 07:43:05 by fluchten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	size_t	len;

	if (!str || !fd)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (!fd)
		return ;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}	
	else if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
}

void	ft_print_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("Try ./client <PID> <STRING_TO_SEND>\n", 2);
	exit(EXIT_FAILURE);
}
