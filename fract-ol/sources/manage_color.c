/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:20:33 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 16:22:32 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static void color_shift_striped(t_fractol *fractol)
{
	if(fractol->color_pattern == 2)
		set_color_zebra(fractol, fractol->color);
	else if (fractol->color_pattern == 3)
		set_color_triad(fractol, fractol->color);
	else if (fractol->color_pattern == 4)
		set_color_tetra(fractol, fractol->color);
}

void	shift_color(t_fractol *fractol)
{
	int secondary_color;

	fractol->color_pattern = (fractol->color_pattern + 1) % 5;
	reinit_img(fractol);
	if (fractol->color == 0x000000)
		secondary_color = 0x333333;
	else
		secondary_color = fractol->color;
	if (fractol->color_pattern == 0)
		set_color_mono(fractol, secondary_color);
	else if (fractol->color_pattern == 1)
		set_color_multiple(fractol, (int [4]){0x000000, secondary_color,
			get_percent_color(fractol->color, 50), 0xFFFFFF}, 4);
	else
		color_shift_striped(fractol);
}
