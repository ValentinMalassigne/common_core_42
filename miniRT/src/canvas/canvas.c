/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:11 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:47:12 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./canvas.h"
#include "libft.h"

t_canvas	*canvas_create(int width, float aspect, void *arena)
{
	t_canvas	*c;

	c = arena_alloc(arena, sizeof(*c));
	c->width = width;
	c->height = (int)((float)width / aspect);
	c->raster = arena_alloc(arena, sizeof(*c->raster) * c->width * c->height);
	return (c);
}

//pthread_mutex_destroy(&canvas->mut);
void	canvas_destroy(t_canvas *canvas)
{
	(void) canvas;
}

void	canvas_draw(t_canvas *canvas, int x, int y, t_color c)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y <= canvas->height)
	{
		canvas->raster[y * canvas->width + x] = c;
	}
}
