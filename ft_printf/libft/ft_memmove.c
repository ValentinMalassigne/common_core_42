/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:38:10 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 09:17:30 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	size_t			i;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	i = 0;
	if (ptr < ptr2)
	{
		while (i < n)
		{
			ptr[i] = ptr2[i];
			i++;
		}
	}
	else if (ptr > ptr2)
	{
		while (n > 0)
		{
			n--;
			ptr[n] = ptr2[n];
		}
	}
	return (dest);
}
