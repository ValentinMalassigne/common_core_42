/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:38:35 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/10 09:17:30 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_size;
	size_t	src_size;

	if ((!dst || !src) && size == 0)
		return (0);
	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	j = dst_size;
	i = 0;
	if (dst_size < size - 1 && size > 0)
	{
		while (src[i] && dst_size + i < size - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (dst_size >= size)
		dst_size = size;
	return (dst_size + src_size);
}
