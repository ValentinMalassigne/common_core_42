/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:47:56 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:47:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"
#include "mlx.h"

void	graphics_present(t_graphics *grph)
{
	mlx_put_image_to_window(
		grph->mlx_ptr,
		grph->win_ptr,
		grph->framebuffer->ptr,
		0,
		0);
}

void	graphics_update_framebuffer(t_graphics *grph, t_canvas *canvas)
{
	int	i;

	i = -1;
	while (++i < grph->win_height * grph->win_width)
		grph->framebuffer->raster[i] = canvas->raster[i];
}

void	graphics_clear(t_graphics *grph)
{
	int	i;

	i = -1;
	while (++i < grph->win_height * grph->win_width)
		grph->framebuffer->raster[i] = 0;
}
