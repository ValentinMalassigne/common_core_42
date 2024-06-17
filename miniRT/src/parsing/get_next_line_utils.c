/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:47:26 by rluiz             #+#    #+#             */
/*   Updated: 2024/03/26 09:46:02 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_line(char *dest)
{
	int	i;

	i = 0;
	if (!dest)
		return (0);
	while (dest[i] && dest[i] != '\n')
		i++;
	if (dest[i] == '\n')
		return (1);
	return (0);
}

int	ft_strlen_line(char *dest)
{
	int	i;

	i = 0;
	if (!dest)
		return (0);
	while (dest[i] && dest[i] != '\n')
		i++;
	return (i);
}

char	*alloc_join_dest(t_arena *arena, char *src, char *buff, int *i)
{
	char	*dest;

	if (!src)
		dest = arena_alloc(arena, sizeof(char) * ft_strlen_line(buff) + 2);
	else
	{
		dest = arena_alloc(arena, sizeof(char)
				* ft_strlen_line(buff) + ft_strlen(src) + 2);
		while (src[*i])
		{
			dest[*i] = src[*i];
			*(i) = *(i) + 1;
		}
	}
	return (dest);
}

char	*ft_join_line(t_arena *arena, char *src, char *buff)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = alloc_join_dest(arena, src, buff, &i);
	while (buff[j] && buff[j] != '\n')
	{
		dest[i] = buff[j];
		i++;
		j++;
	}
	dest[i] = '\n';
	if (buff[j] == '\n')
		i++;
	dest[i] = '\0';
	if (dest[0] == '\0')
	{
		return (NULL);
	}
	return (dest);
}

void	ft_cute_line(char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] && dest[i] != '\n')
		i++;
	if (dest[i] == '\n')
		i++;
	while (dest[i])
	{
		dest[j] = dest[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}
