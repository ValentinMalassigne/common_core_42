/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:24:12 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 17:51:13 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

int	print_hex(unsigned int decimal, int upper)
{
	if (decimal == 0)
		ft_putchar_fd('0', 1);
	else
		put_hex(decimal, upper);
	return (hex_len(decimal));
}
