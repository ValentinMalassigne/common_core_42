/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 00:39:53 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:04 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		found_at;
	char	*big_ptr;
	char	*little_ptr;

	if ((!big || !little) && len == 0)
		return (0);
	big_ptr = (char *)big;
	little_ptr = (char *)little;
	i = 0;
	if (little_ptr[0] == '\0')
		return (big_ptr);
	while (*big_ptr && 0 < len)
	{
		found_at = i;
		while (big_ptr[i] == little_ptr[i] && little_ptr[i])
			i++;
		if (little_ptr[i] == '\0' && i <= len)
			return (big_ptr + found_at);
		i = 0;
		big_ptr++;
		len--;
	}
	return (NULL);
}
