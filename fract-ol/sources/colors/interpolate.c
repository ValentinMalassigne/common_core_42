/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:32:08 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 16:22:57 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static int	interpolate(int start_color, int end_color, double fraction)
{
	int	start_rgb[3];
	int	end_rgb[3];

	start_rgb[0] = ((start_color >> 16) & 0xFF);
	start_rgb[1] = ((start_color >> 8) & 0xFF);
	start_rgb[2] = ((start_color >> 0) & 0xFF);
	end_rgb[0] = ((end_color >> 16) & 0xFF);
	end_rgb[1] = ((end_color >> 8) & 0xFF);
	end_rgb[2] = ((end_color >> 0) & 0xFF);
	start_rgb[0] = (end_rgb[0] - start_rgb[0]) * fraction + start_rgb[0];
	start_rgb[1] = (end_rgb[1] - start_rgb[1]) * fraction + start_rgb[1];
	start_rgb[2] = (end_rgb[2] - start_rgb[2]) * fraction + start_rgb[2];
	return (0xFF << 24 | start_rgb[0] << 16 | start_rgb[1] << 8 | start_rgb[2]);
}

void	set_color_mono(t_fractol *fractol, int color)
{
	int		i;
	int		j;
	double	fraction;
	int		color1;
	int		color2;

	color1 = 0x000000;
	color2 = color;
	i = 0;
	while (i < ITERATIONS_LIMIT)
	{
		j = 0;
		while (j < ITERATIONS_LIMIT / 2)
		{
			fraction = (double)j / (ITERATIONS_LIMIT / 2);
			fractol->colors[i + j] = interpolate(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = 0xFFFFFF;
		i += j;
	}
	fractol->colors[ITERATIONS_LIMIT - 1] = 0;
}

void	set_color_multiple(t_fractol *fractol, int colors[4], int length)
{
	int	i;
	int	j;
	int x;
	double fraction;

	i = 0;
	x = 0;
	while (i < ITERATIONS_LIMIT)
	{
		j = 0;
		while ((i + j) < ITERATIONS_LIMIT && j < (ITERATIONS_LIMIT / (length - 1)))
		{
			fraction = (double)j / (ITERATIONS_LIMIT / (length -1));
			fractol->colors[i + j] = interpolate(colors[x], colors[x + 1], fraction);
			j++;
		}
		x++;
		i += j;
	}
	fractol->colors[ITERATIONS_LIMIT -1] = 0;
}