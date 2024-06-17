/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:01 by vmalassi          #+#    #+#             */
/*   Updated: 2024/04/01 11:48:02 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

static int	graphics_init_mlx(t_graphics *grph)
{
	grph->mlx_ptr = mlx_init();
	if (grph->mlx_ptr == NULL)
	{
		printf("Error: failed to initialize mlx instance\n");
		return (EXIT_FAILURE);
	}
	grph->win_ptr = mlx_new_window(
			grph->mlx_ptr,
			grph->win_width,
			grph->win_height,
			"miniRT");
	if (grph->win_ptr == NULL)
	{
		printf("Error: failed to create mlx window\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static t_mlx_image	*graphics_create_mlx_image(
	void *mlx_ptr, int width, int height, void *arena)
{
	t_mlx_image	*img;

	img = arena_alloc(arena, sizeof(*img));
	img->ptr = mlx_new_image(
			mlx_ptr,
			width,
			height);
	if (img->ptr == NULL)
	{
		printf("Error: failed to create mlx image\n");
		return (NULL);
	}
	img->raster = (t_color *)mlx_get_data_addr(
			img->ptr, &img->bpp, &img->size_line, &img->endian);
	return (img);
}

t_graphics	*graphics_create(int width, float aspect, void *arena)
{
	t_graphics	*grph;

	grph = arena_alloc(arena, sizeof(*grph));
	grph->win_width = width;
	grph->win_height = (int)((float)width / aspect);
	if (graphics_init_mlx(grph) == EXIT_FAILURE)
	{
		graphics_destroy(grph);
		return (NULL);
	}
	grph->framebuffer = graphics_create_mlx_image(
			grph->mlx_ptr, grph->win_width, grph->win_height, arena);
	if (grph->framebuffer == NULL)
	{
		graphics_destroy(grph);
		return (NULL);
	}
	return (grph);
}

void	graphics_destroy(t_graphics *grph)
{
	if (grph != NULL)
	{
		if (grph->framebuffer != NULL)
			mlx_destroy_image(grph->mlx_ptr, grph->framebuffer->ptr);
		if (grph->win_ptr != NULL)
			mlx_destroy_window(grph->mlx_ptr, grph->win_ptr);
		if (grph->mlx_ptr != NULL)
		{
			mlx_destroy_display(grph->mlx_ptr);
			free(grph->mlx_ptr);
		}
	}
}
