/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmalassi <vmalassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:24:17 by vmalassi          #+#    #+#             */
/*   Updated: 2023/11/07 16:23:07 by vmalassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fractol.h"

static void set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	fractol->data[x * 4 + y * WIDTH * 4] = color;
	fractol->data[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	fractol->data[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	fractol->data[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

static int calculate_fractal(t_fractol *fractol, double pr, double pi)
{
	int iterations;

	if (fractol->set == 1)
		iterations = mandelbrot(pr, pi);
	else if (fractol->set == 2)
		iterations = julia(fractol, pr, pi);
	return (iterations);
}

void	render(t_fractol *fractol)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	int		iterations;

	mlx_clear_window(fractol->mlx, fractol->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pr = fractol->min_r + (double)x * (fractol->max_r - fractol->min_r) / WIDTH;
			pi = fractol->max_i + (double)y * (fractol->min_i - fractol->max_i) / HEIGHT;
			iterations = calculate_fractal(fractol, pr, pi);
			set_pixel_color(fractol, x, y, fractol->colors[iterations]);
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}