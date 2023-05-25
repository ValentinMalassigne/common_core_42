/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:24:29 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 14:27:59 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../includes/libft.h"

int	print_str(char *str)
{
	if (str)
	{
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	ft_putstr_fd("(null)", 1);
	return (6);
}
