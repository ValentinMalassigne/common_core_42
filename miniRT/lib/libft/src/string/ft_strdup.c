/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:46:28 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:46:29 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(t_arena *arena, const char *s)
{
	char	*res;
	size_t	i;

	res = arena_alloc(arena, sizeof(char) * (1 + ft_strlen(s)));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
