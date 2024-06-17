/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:46:43 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:46:44 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	tmp;

	if (str)
	{
		len = ft_strlen(str);
		i = -1;
		j = len - 1;
		while (++i < len / 2)
		{
			tmp = str[i];
			str[i] = str[j];
			str[j] = tmp;
			j--;
		}
	}
	return (str);
}
