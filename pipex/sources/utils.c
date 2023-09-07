/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:40:24 by vmalassi          #+#    #+#             */
/*   Updated: 2023/09/07 13:33:56 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include <errno.h>
#include <string.h>

int	set_pipe(int pipex[2])
{
	if (pipe(pipex) == -1)
	{
		ft_printf("Error : pipe creation failure\n");
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
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
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
