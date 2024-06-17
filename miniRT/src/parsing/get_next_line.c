/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:45:07 by vmalassi          #+#    #+#             */
/*   Updated: 2024/03/26 09:45:50 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_next_line(t_arena *arena, int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	int			i;
	char		*dest;

	i = 1;
	dest = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (ft_check_line(buff) == 1)
	{
		ft_cute_line(buff);
		dest = ft_join_line(arena, dest, buff);
	}
	while (i > 0 && ft_check_line(buff) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			return (dest);
		buff[i] = '\0';
		dest = ft_join_line(arena, dest, buff);
	}
	return (dest);
}
