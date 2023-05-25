/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:59:22 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/23 08:49:39 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_until_line(int fd, char *read_output)
{
	char	*buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!(ft_strchr(read_output, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		read_output = ft_strjoin(read_output, buffer);
	}
	free(buffer);
	return (read_output);
}

char	*get_next_line(int fd)
{
	static char	*read_output[1000];
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	read_output[fd] = read_until_line(fd, read_output[fd]);
	if (!read_output[fd])
		return (NULL);
	extracted_line = ft_get_line(read_output[fd]);
	read_output[fd] = ft_remove_line(read_output[fd]);
	return (extracted_line);
}
