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
