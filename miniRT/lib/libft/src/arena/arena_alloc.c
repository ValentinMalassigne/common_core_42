/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluiz <rluiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:22:50 by rluiz             #+#    #+#             */
/*   Updated: 2023/12/23 17:06:37 by rluiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_internal.h"

void	*arena_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((unsigned char *)s)[i] = c;
	return (s);
}

static int	is_power_of_two(uintptr_t x)
{
	return ((x & (x - 1)) == 0);
}

static uintptr_t	align_forward(uintptr_t ptr, size_t align)
{
	uintptr_t	p;
	uintptr_t	a;
	uintptr_t	modulo;

	if (!is_power_of_two(align))
		exit(1);
	p = ptr;
	a = (uintptr_t)align;
	modulo = p % a;
	if (modulo != 0)
		p += a - modulo;
	return (p);
}

void	*arena_alloc(t_arena *a, size_t size)
{
	uintptr_t	curr_ptr;
	uintptr_t	offset;
	void		*ptr;

	curr_ptr = (uintptr_t)a->buf + (uintptr_t)a->curr_offset;
	offset = align_forward(curr_ptr, sizeof(void *));
	offset -= (uintptr_t)a->buf;
	if (offset + size > a->buf_size
		|| offset + size > a->buf_size - a->tempo_offset)
		return (NULL);
	ptr = &((unsigned char *)a->buf)[offset];
	a->prev_offset = offset;
	a->curr_offset = offset + size;
	arena_memset(ptr, 0, size);
	return (ptr);
}

void	*arena_temp_alloc(t_arena *a, size_t size)
{
	uintptr_t	curr_temp_ptr;
	void		*ptr;

	curr_temp_ptr = (uintptr_t)a->buf + (uintptr_t)a->buf_size
		- (uintptr_t)a->tempo_offset - (uintptr_t)size;
	if (curr_temp_ptr <= (uintptr_t)a->buf + (uintptr_t)a->curr_offset)
		return (NULL);
	ptr = (unsigned char *)curr_temp_ptr;
	a->tempo_offset = a->tempo_offset + size;
	return (ptr);
}
