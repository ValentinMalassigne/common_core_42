/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:04:35 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/23 09:08:17 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	if (!s)
		return (0);
	res = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			res = ((char *)s);
			break ;
		}
		s++;
	}
	if (!*s && (char)c == *s)
		res = ((char *)s);
	return (res);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*res;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		*s1 = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	res = malloc((ft_strlen((const char *)s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	while (*s2)
		res[i++] = *s2++;
	res[i] = 0;
	free(s1);
	return (res);
}

char	*ft_get_line(const char *s1)
{
	int		i;
	char	*res;

	i = 0;
	if (!*s1)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	res = malloc((i + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		res[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		res[i] = '\n';
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_remove_line(char *s1)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i])
	{
		free(s1);
		return (NULL);
	}
	res = malloc((ft_strlen(s1) - i + 1));
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	res[j] = 0;
	free(s1);
	return (res);
}
