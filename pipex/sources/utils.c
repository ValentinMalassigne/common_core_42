/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:40:24 by vmalassi          #+#    #+#             */
/*   Updated: 2023/07/20 17:40:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	set_pipe(int pipex[2])
{
	if (pipe(pipex) == -1)
	{
		ft_printf("TODO pipe creation failure\n");
		return (-1);
	}
	return (0);
}

void	close_pipe(int pipex[2])
{
	close(pipex[0]);
	close(pipex[1]);
}

int	open_file(char *path, int open_type)
{
	int	file_fd;

	if (open_type == 0)
		file_fd = open(path, O_RDONLY, 0644);
	if (open_type == 1)
		file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
		exit(0);
	return (file_fd);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}