/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:07:19 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 12:01:50 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	exit_error(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_and_exit_error(t_arena *arena, char *msg)
{
	arena_destroy(arena);
	exit_error(msg);
}
