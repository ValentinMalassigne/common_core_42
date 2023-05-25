/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_deci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:28:45 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 15:37:43 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"

int	print_deci(int nbr)
{
	ft_putnbr_fd(nbr, 1);
	return (int_length(nbr));
}
