/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:39:14 by vmalassi          #+#    #+#             */
/*   Updated: 2023/04/13 15:31:06 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (char) c)
		{
			res = ((char *)s);
		}
		s++;
	}
	if (!*s && (char) c == *s)
	{
		res = ((char *)s);
	}
	return (res);
}
