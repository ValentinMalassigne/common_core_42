/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:44:10 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 15:59:20 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fractol.h"

int	get_percent_color(int color, double percent)
{
	int		rgb[3];
	int		trgb[3];
	double	percentage;

	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 0) & 0xFF;
	percentage = (percent / 100) * 256;
	trgb[0] = (rgb[0] + percentage) - 256;
	trgb[1] = (rgb[1] + percentage) - 256;
	trgb[2] = (rgb[2] + percentage) - 256;
	return (0xFF << 24 | trgb[0] << 16 | trgb[1] << 8 | trgb[2]);
}

static void fill_color_stripe(t_fractol *fractol, int color, int stripe)
{
	int	i;

	i = 0;
	while (i < ITERATIONS_LIMIT)
	{
		fractol->colors[i] = color;
		i += stripe;
	}
}

void	set_color_zebra(t_fractol *fractol, int color)
{
	int	color2;

	color2 = get_percent_color(color, 50);
	fill_color_stripe(fractol, color, 1);
	fill_color_stripe(fractol, color2, 2);
	fractol->colors[ITERATIONS_LIMIT - 1] = 0;
}

void set_color_triad(t_fractol *fractol, int color)
{
	int triad[2];

	triad[0] = get_percent_color(color, 33);
	triad[1] = get_percent_color(color, 66);
	fill_color_stripe(fractol, color, 1);
	fill_color_stripe(fractol, triad[0], 2);
	fill_color_stripe(fractol, triad[1], 3);
	fractol->colors[ITERATIONS_LIMIT - 1] = 0;
}

void	set_color_tetra(t_fractol *fractol, int color)
{
	int tetra[3];

	tetra[0] = get_percent_color(color, 25);
	tetra[1] = get_percent_color(color, 50);
	tetra[2] = get_percent_color(color, 75);
	fill_color_stripe(fractol, color, 1);
	fill_color_stripe(fractol, tetra[0], 2);
	fill_color_stripe(fractol, tetra[1], 3);
	fill_color_stripe(fractol, tetra[2], 4);
	fractol->colors[ITERATIONS_LIMIT - 1] = 0;
}
