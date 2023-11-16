/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:32:08 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/10 20:44:22 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static int	get_wave_color(int start_color, int end_color, double fraction)
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
	return ((0 << 24) + ((start_rgb[0]) << 16)
		+ ((start_rgb[1]) << 8) + (start_rgb[2]));
}

void	set_color_waves(t_fractol *fractol, int color)
{
	int		i;
	int		j;
	double	fraction;
	int		color1;
	int		color2;

	color1 = 0;
	color2 = color;
	i = 0;
	while (i < ITERATIONS_LIMIT)
	{
		j = 0;
		while (j < ITERATIONS_LIMIT / 2)
		{
			fraction = (double)j / (ITERATIONS_LIMIT / 2);
			fractol->colors[i + j] = get_wave_color(color1, color2, fraction);
			j++;
		}
		color1 = color2;
		color2 = (255 << 16) + (255 << 8) + (255);
		i += j;
	}
	fractol->colors[ITERATIONS_LIMIT - 1] = 0;
}
