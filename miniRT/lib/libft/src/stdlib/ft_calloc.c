/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:45:45 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:45:46 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	if (((nmemb > 65535 || size > 65535)) && (size_t)-1 / nmemb < size)
		return (NULL);
	res = malloc(sizeof(char) * size * nmemb);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		((char *)res)[i] = '\0';
		i++;
	}
	return (res);
}
