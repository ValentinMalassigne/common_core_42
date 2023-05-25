/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:23:14 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 16:48:13 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	unsigned_int_length(unsigned int nbr)
{
	int	length;

	length = 0;
	if (nbr == 0)
		length = 1;
	while (nbr != 0)
	{
		length++;
		(nbr /= 10);
	}
	return (length);
}

int	int_length(int nbr)
{
	int	length;

	length = 0;
	if (nbr == 0)
		length = 1;
	if (nbr < 0)
		length++;
	while (nbr != 0)
	{
		length++;
		nbr /= 10;
	}
	return (length);
}

int	hex_len(unsigned long decimal)
{
	int	length;

	length = 0;
	if (decimal == 0)
		length = 1;
	while (decimal != 0)
	{
		length++;
		decimal /= 16;
	}
	return (length);
}

void	put_unsigned(unsigned int n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		put_unsigned(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

void	put_hex(unsigned long decimal, int upper)
{
	if (decimal == 0)
		return ;
	put_hex(decimal / 16, upper);
	decimal %= 16;
	if (decimal < 10)
		ft_putchar_fd(decimal + '0', 1);
	else
	{
		if (upper == 0)
			ft_putchar_fd(decimal - 10 + 'a', 1);
		else
			ft_putchar_fd(decimal - 10 + 'A', 1);
	}
}
