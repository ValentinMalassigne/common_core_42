/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:24:12 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 15:26:47 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

int	print_hex(unsigned int decimal, int upper)
{
	if (decimal == 0)
		ft_putchar_fd('0', 1);
	else
		put_hex(decimal, upper);
	return (hex_len(decimal));
}
