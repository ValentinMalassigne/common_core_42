/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:59:22 by vmalassi          #+#    #+#             */
/*   Updated: 2023/05/23 08:48:42 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*read_output;
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	read_output = read_until_line(fd, read_output);
	if (!read_output)
		return (NULL);
	extracted_line = ft_get_line(read_output);
	read_output = ft_remove_line(read_output);
	return (extracted_line);
}
