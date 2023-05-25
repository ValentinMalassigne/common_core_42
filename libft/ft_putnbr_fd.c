/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:13:55 by vmalassi          #+#    #+#             */
/*   Updated: 2023/04/17 18:21:04 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	unb;

	unb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		unb = -n;
	}
	if (unb < 10)
	{
		ft_putchar_fd(unb + '0', fd);
	}
	else
	{
		ft_putnbr_fd(unb / 10, fd);
		ft_putchar_fd((unb % 10) + '0', fd);
	}
}
