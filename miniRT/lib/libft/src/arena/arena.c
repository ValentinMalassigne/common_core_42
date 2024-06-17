/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:22:08 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/23 17:06:24 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_internal.h"

void	*arena_init(size_t buffer_size)
{
	t_arena	*a;
	void	*buf;

	buf = malloc(buffer_size);
	if (!buf)
		return (NULL);
	a = malloc(sizeof(t_arena));
	if (!a)
		return (NULL);
	a->buf = buf;
	a->buf_size = buffer_size;
	a->curr_offset = 0;
	a->prev_offset = 0;
	a->tempo_offset = 0;
	return (a);
}

void	arena_reset(t_arena *a)
{
	a->curr_offset = 0;
	a->prev_offset = 0;
	a->tempo_offset = 0;
}

void	arena_destroy(t_arena *a)
{
	arena_reset(a);
	if (a->buf)
		free(a->buf);
	free(a);
}

void	arena_memset_temp(t_arena *a)
{
	arena_memset(a->buf + (uintptr_t)a->buf_size
		- (uintptr_t)a->tempo_offset, 0, a->tempo_offset);
	a->tempo_offset = 0;
}
