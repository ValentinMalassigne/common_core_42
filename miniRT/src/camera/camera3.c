/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:48:09 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 10:51:06 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "canvas/canvas.h"
#include "engine/engine.h"
#include "objects/objects.h"
#include "libft.h"
#include "ray.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

void	*camera_render(void *vargp)
{
	t_render	*rd;
	t_color		color;
	t_vec3		final_color;
	int			i;
	int			j;

	rd = (t_render *)vargp;
	j = 0;
	while (j < rd->canvas->height)
	{
		i = 0;
		while (i < rd->canvas->width)
		{
			final_color = calc_objects(rd, i, j);
			color = color_vec3(final_color);
			canvas_draw(rd->canvas, i, j, color);
			i++;
		}
		j++;
	}
	return (NULL);
}
