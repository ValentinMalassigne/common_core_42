/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:38:02 by vmalassi          #+#    #+#             */
/*   Updated: 2023/04/18 09:55:44 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;

	if (dest == NULL && src == NULL && n != 0)
		return (dest);
	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (0 < n)
	{
		n--;
		ptr[n] = ptr2[n];
	}
	return (dest);
}
