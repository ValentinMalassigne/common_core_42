/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:08:52 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:04 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	char	*substring;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (start >= s_len)
	{
		substring = malloc(1);
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (s_len - start < len)
		substr_len = s_len - start;
	else
		substr_len = len;
	substring = malloc(substr_len + 1);
	if (!substring)
		return (NULL);
	ft_memcpy(substring, s + start, substr_len);
	substring[substr_len] = '\0';
	return (substring);
}
