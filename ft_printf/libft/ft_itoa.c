/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:47:41 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 09:17:30 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	get_number_length(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		length++;
	if (n < 0)
		length++;
	while (n != 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int				i;
	int				number_length;
	char			*number;
	unsigned int	un;

	i = 0;
	number_length = get_number_length(n);
	number = malloc((number_length + 1) * sizeof(char));
	if (!number)
		return (NULL);
	if (n < 0)
		un = -n;
	else
		un = n;
	while (i < number_length)
	{
		number[number_length - i - 1] = un % 10 + '0';
		un = un / 10;
		i++;
	}
	number[i] = 0;
	if (n < 0)
		number[0] = '-';
	return (number);
}
