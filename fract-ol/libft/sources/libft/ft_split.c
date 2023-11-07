/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:19:56 by vmalassi          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:04 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static char	*trim_str(char const *s, char c)
{
	char	set[2];
	char	*trimmed;

	if (!s)
		return (NULL);
	set[0] = c;
	set[1] = '\0';
	trimmed = ft_strtrim(s, set);
	return (trimmed);
}

static int	count_splits(char *s, char c)
{
	int	count;

	count = 1;
	if (ft_strlen(s) == 0)
		return (0);
	while (*s)
	{
		if (*s == c && *(s + 1))
		{
			count++;
			while (*s == c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c)
{
	int		word_length;
	char	*word;
	int		i;

	i = 0;
	word_length = 0;
	while (s[word_length] != c && s[word_length])
		word_length++;
	word = malloc((word_length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < word_length)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		splits_count;
	int		i;
	char	**res;
	char	*trimmed;
	char	*to_free;

	i = 0;
	trimmed = trim_str(s, c);
	if (!trimmed)
		return (NULL);
	to_free = trimmed;
	splits_count = count_splits(trimmed, c);
	res = malloc((splits_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < splits_count)
	{
		res[i] = get_word(trimmed, c);
		trimmed += ft_strlen(res[i++]);
		while (*trimmed == c && *trimmed)
			trimmed++;
	}
	res[i] = NULL;
	free(to_free);
	return (res);
}
