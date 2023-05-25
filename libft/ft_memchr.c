/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:39:34 by vmalassi          #+#    #+#             */
/*   Updated: 2023/04/12 00:39:37 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*res;

	res = (unsigned char *)s;
	while (0 < n)
	{
		if (*res == (unsigned char)c)
			return (res);
		res++;
		n--;
	}
	return (NULL);
}
