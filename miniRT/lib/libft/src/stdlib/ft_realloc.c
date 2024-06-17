/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:45:59 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:46:00 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*res;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	res = malloc(size);
	if (!res)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(res, ptr, size);
		free(ptr);
	}
	return (res);
}
